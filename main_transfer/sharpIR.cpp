/** EGR 3380
 * Team 5 - Loose Screws (Transfer)
 * Filename: sharpIR.cpp
 * Original Author name: Giuseppe Masino
 * Forked by: Daechan Lee
 * Last Updated: 11/26/2023
 * Version 1.0
 * 
 * Source code: https://github.com/qub1750ul/Arduino_SharpIR/tree/master
 *
 * Defines the SharpIR object to easily access and read sensor's distance.
 */

#include "sharpIR.h"

/* getDistance()
 *
 * Outputs the distance that the sensor is detecting an object to in cm.
 * This is function was not modified from the original SharpIR object in github.
 *
 * Parameters:
 *   avoidBurstRead - sets whether or not the sensor should read in burst.
 *
 * Return value:
 *   detected distance.
 */
uint8_t SharpIR::getDistance( bool avoidBurstRead ) {
	uint8_t distance;

	if( !avoidBurstRead ) {
		while(millis() <= lastTime + 20) {} //wait for sensor's sampling time
	}
	lastTime = millis();

	switch( sensorType ) {
		case GP2Y0A21YK0F :
			distance = 4800/(analogRead(pin)-20);

			if(distance > 80) return 81;
			else if(distance < 6) return 5;
			else return distance;

			break;

		default: break;
	}
}

/* senseInboundBlockUpTo()
 *
 * Senses the inbound block. This senses the upper limit of the code, and
 * if the sensed distance is less than the upper limit, the function returns
 * so that the driver may continue with its procedure. In other words, it waits
 * until a block is placed at a position less than or equal to the
 * limit argument.
 *
 * Parameters:
 *   limit - upper limit of the distance that the block could be in.
 *
 * Return value:
 *   void.
 */
void SharpIR::senseInboundBlockUpTo(uint8_t limit) {
	bool firstMeasure = false;
	uint8_t distance = getDistance();
	delay(100); //safety

	if(distance < limit) firstMeasure = true; 
	do {
		distance = getDistance();
		if(distance < limit && !firstMeasure) {
			delay(200); //safety
			firstMeasure = true;
		}
        delay(100);
        //Serial.println(distance);
	} while(distance > limit);
}

/* senseOutboundBlockUpTo()
 *
 * Senses the outbound block. This senses the lower limit of the code, and
 * if the sensed distance is greater than the lower limit, the function returns
 * so that the driver may continue with its procedure. In other words, it waits
 * until there is a clearing in the outbound area.
 * 
 * Parameters:
 *   limit - lower limit of the distance that defines a clear space.
 *
 * Return value:
 *   void.
 */
void SharpIR::senseOutboundBlockUpTo(uint8_t limit) {
	bool firstMeasure = false;
	uint8_t distance = getDistance();
	delay(100); //safety

	if(distance > limit) firstMeasure = true; 
	do {
		distance = getDistance();
		if(distance > limit && !firstMeasure) {
			delay(200); //safety
			firstMeasure = true;
		}
        delay(100);
		//Serial.println(distance);
	} while(distance < limit);
	delay(300);
}