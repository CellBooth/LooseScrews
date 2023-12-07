//lead screw up
#include <AccelStepper.h>
// Lead Screw
const int dirPinSLead = 4;
const int stepPinSLead = 5;

const int leadScrewInboundHigh = -376; //380
const int leadScrewOutboundHigh = -580;
const int leadScrewLow = -855; // -850; //was -880 originally

const uint32_t fastSpeed = 800;
const uint32_t mediumSpeed = 600;
const uint32_t slowSpeed = 500;


void StepTo(AccelStepper *stepper, int pos) {
    stepper->moveTo(pos);
    while(stepper->currentPosition() != pos) {
        stepper->run();
    }
}

// Instances
AccelStepper stepperLead(1, stepPinSLead, dirPinSLead);
int pos = 400; //CHANGE ME: accordingly

void setup() {
    delay(2200);
    stepperLead.setMaxSpeed(slowSpeed);
    stepperLead.setAcceleration(mediumSpeed);
    StepTo(&stepperLead, pos);
}

void loop() {}
