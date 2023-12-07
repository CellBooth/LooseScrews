/** EGR 3380
 * Team 5 - Loose Screws (Transfer)
 * Filename: main_transfer.ino
 * Author Name: Daechan Lee
 * Last Updated: 11/28/2023
 * Version 3.0
 *
 * This driver is the main code to execute the transfer subsystem.
 * Note that the physical positions of the subsystem are as follows:
 *   - Lead Screw motor is positioned so that the gear box is the highest point
 *   - Conveyor Belt's motor is positioned so that the entire structure
 *     is as far left (facing from inbound) as possible.
 */

#include <AccelStepper.h>
#include <Servo.h>
#include "sharpIR.h"
#include "constants.h"

#define countPerSide 4;

typedef enum Direction {
    RIGHT = 1,
    LEFT = -1
};

typedef enum FunctionState {
    BASE_STATE = 0,
    SENSE_INBOUND = 1,
    MOVE_TO_INBOUND = 2,
    PICK_BLOCK = 3,
    SENSE_OUTBOUND = 4,
    MOVE_TO_OUTBOUND = 5,
    DROP_BLOCK = 6,
    SETUP_NEXT = 7,
    PAUSE = 8 //for testing purposes
} FunctionState;

//Instantiate
AccelStepper stepperConveyor(1, stepPinSC, dirPinSC);
AccelStepper stepperLead(1, stepPinSLead, dirPinSLead);
AccelStepper stepperLazy(1, stepPinSLazy, dirPinSLazy);

Servo servoExtender;
Servo servoGrabber;
SharpIR sensor(SharpIR::GP2Y0A21YK0F, A15);


static enum Direction side = RIGHT;
static enum FunctionState currentState;
static uint8_t numCount = 0;

//Function definitions
void StepTo(AccelStepper *stepper, int pos);
void ReadSwitchInput();

/* setup()
 *
 * This function sets appropriate values and attaches pins accordingly.
 *
 * Parameters:
 *   none.
 *
 * Return value:
 *   void.
 */
void setup() {
    Serial.begin(9600);
    delay(4000); //necessary to avoid jitter

    //conveyor
    stepperConveyor.setMaxSpeed(fastSpeed);
    stepperConveyor.setAcceleration(fastSpeed);
    StepTo(&stepperConveyor, conveyorCenter);
    delay(3000);

    //lead screw
    stepperLead.setMaxSpeed(mediumSpeed);
    stepperLead.setAcceleration(mediumSpeed);

    //lazy susan
    stepperLazy.setMaxSpeed(fastSpeed);
    stepperLazy.setAcceleration(fastSpeed);

    ////servo
    servoExtender.attach(extenderPin);
    //FIXME:
    servoExtender.write(extenderFullyRetractedPos);

    servoGrabber.attach(grabberPin);
    servoGrabber.write(grabberOpenPos); 


    Serial.println("Setup");
    currentState = BASE_STATE;
    
    //digitalWrite is used to send a signal to outbound team
    //so that they will know when the block is dropped.
    pinMode(outBoundReady, OUTPUT);
    digitalWrite(outBoundReady, LOW);

    pinMode(buttonPin, INPUT);
    pinMode(switchPin, INPUT);
    
    ReadSwitchInput();
}

void loop() {
    int offset;
    offset = side == RIGHT ? horizontalOffsetRight : horizontalOffsetLeft;
    switch(currentState) {
        case BASE_STATE:
            StepTo(&stepperLead, leadScrewInboundHigh);
            StepTo(&stepperLazy, 0);
            currentState = SENSE_INBOUND;
            break;

        case SENSE_INBOUND:
            StepTo(&stepperConveyor, conveyorCenter + side*offset);
            delay(1000);
            
            sensor.senseInboundBlockUpTo(inDistance);
            currentState = MOVE_TO_INBOUND;
            break;

        case MOVE_TO_INBOUND:
            StepTo(&stepperConveyor, conveyorCenter);
            StepTo(&stepperLazy, -1 * side * rotateArmInbound);
            StepTo(&stepperConveyor, conveyorCenter + side * offset);

            delay(100);
            servoExtender.write(extendInboundPos);
            delay(2000);

            currentState = PICK_BLOCK;
            break;
        
        case PICK_BLOCK:
            StepTo(&stepperLead, leadScrewLow);
            delay(500);

            servoGrabber.write(grabberClosedPos);
            delay(20);
            StepTo(&stepperLead, leadScrewInboundHigh);
            delay(300);

            currentState = SENSE_OUTBOUND;
            break;

        case SENSE_OUTBOUND:
            servoExtender.write(extenderRetractedPos);
            delay(1800);

            StepTo(&stepperConveyor, conveyorCenter);
            sensor.senseOutboundBlockUpTo(outDistance);            
            delay(20);

            StepTo(&stepperConveyor, conveyorCenter + side * (offset / 2));
            delay(300);
            currentState = MOVE_TO_OUTBOUND;
            break;
        
        case MOVE_TO_OUTBOUND:
            StepTo(&stepperLazy, rotateArmOutbound);
            StepTo(&stepperConveyor, conveyorCenter);
            delay(300);

            currentState = DROP_BLOCK;
            break;

        case DROP_BLOCK:
            servoExtender.write(extendOutboundPos);
            delay(10);

            //-26 to accommodate for outbound's height
            StepTo(&stepperLead, leadScrewLow - 250); //280 if slow, if fast 250
            delay(800);

            servoGrabber.write(grabberOpenPos);
            digitalWrite(outBoundReady, HIGH);
            
            delay(10);
            StepTo(&stepperLead, leadScrewInboundHigh);
            servoExtender.write(extenderFullyRetractedPos);
            digitalWrite(outBoundReady, LOW);

            currentState = SETUP_NEXT;
            break;
            
        case SETUP_NEXT:
            Serial.println("SETUP\n");
            numCount++;
            if(numCount == 4) {
                side = -1 * side;
            }

            else if(numCount == 8) {
                ReadSwitchInput();
                numCount = 0;
            }

            currentState = SENSE_INBOUND;
            break;

        case PAUSE: 
            Serial.println("in PAUSE\n");
        default:
            currentState = PAUSE;
    }
}

//Function Definitions
/* StepTo()
 *
 * Reduces redundant code to control stepper drivers to a specified position.
 *
 * Parameters:
 *   stepper - instantiated stepper object.
 *   pos - destination.
 *
 * Return value:
 *   void.
 */
void StepTo(AccelStepper *stepper, int pos) {
    stepper->moveTo(pos);
    while(stepper->currentPosition() != pos) {
        stepper->run();
    }
}

/* ReadSwitchInput()
 *
 * Reads input from the switch with conditions such as button being pressed.
 *
 * Parameters:
 *   none.
 *
 * Return value:
 *   void.
 */
void ReadSwitchInput() {
    Serial.println("ReadingSwitchInput\n");
    
    while(digitalRead(buttonPin) != HIGH) {
        delay(200);
        Serial.println("BUTTON LOW... PRESS BUTTON TO INITIATE");
    }
    //side = digitalRead(switchPin) ? RIGHT : LEFT;
    if(digitalRead(switchPin)) {
        Serial.println("side: ");
        Serial.println(side);
        side = RIGHT;
    }
    else {
        side = LEFT;
    }
}
