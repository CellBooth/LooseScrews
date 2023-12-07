/** EGR 3380
 * Team 5 - Loose Screws (Transfer)
 * Filename: constants.h
 * Author Name: Daechan Lee
 * Last Updated: 11/26/2023
 * Version 3.0
 *
 * This header file initializes constants used throughout main.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

//Pins
// Conveyor Belt Driver
const uint8_t dirPinSC = 2; //2 ,3
const uint8_t stepPinSC = 3;

// Lead Screw Driver
const uint8_t dirPinSLead = 4; //4,5
const uint8_t stepPinSLead = 5;
//const uint8_t enablePinS2 = 6;

// Lazy Susan Driver
//NOTE: PIN 12, 13 combination fails.
const uint8_t dirPinSLazy = 8;
const uint8_t stepPinSLazy = 9;


//Stepper constants
const int conveyorLeft = 0;
const int conveyorCenter = 258; //268 //258
const int horizontalOffsetRight = 268; //254 == 2 inches + is right //even
const int horizontalOffsetLeft = 254; //254 == 2 inches + is right //even

//To go faster:
const uint32_t fastSpeed = 1300;
const uint32_t mediumSpeed = 1100;
const uint32_t slowSpeed = 900;
/* const uint32_t fastSpeed = 900;
const uint32_t mediumSpeed = 600;
const uint32_t slowSpeed = 500; */

//Lead Screw: top position = top -580, block pick positon -880
const int leadScrewInboundHigh = -376; //380
const int leadScrewOutboundHigh = -580;
const int leadScrewLow = -855; // -850; //was -880 originally;

//Lazy Susan
const int rotateArmInbound = 299;
const int rotateArmOutbound = 0;


//Servo 
const int extenderPin = 42;
const int grabberPin = 44;

const int grabberOpenPos = 36;
const int grabberClosedPos = 19;

const int extenderFullyRetractedPos = 120;
const int extenderRetractedPos = 134; //min 120
const int extendOutboundPos = 164; //max 172
const int extendInboundPos = 163;

//Sensor
//pin is directly implemented
const uint8_t inDistance = 10; //cm
const uint8_t outDistance = 13;

//Read Button
const uint8_t buttonPin = 50;

//Switch
const uint8_t switchPin = 52;

//Pin to Outbound
const uint8_t outBoundReady = 53;
#endif //CONSTANTS_H