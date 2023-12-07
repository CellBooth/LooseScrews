/** EGR 3380
 * Team 5 - Loose Screws (Transfer)
 * Filename: sharpIR.h
 * Original Author name: Giuseppe Masino
 * Forked by: Daechan Lee
 * Last Updated: 11/26/2023
 * Version 1.0
 * 
 * Source code: https://github.com/qub1750ul/Arduino_SharpIR/tree/master
 *
 * Declares the SharpIR object to easily access and read sensor's distance
 */

#ifndef SHARPIR_H
#define SHARPIR_H
#include <Arduino.h>

/* SharpIR is an sensor that can get a distance from an infrared sensor that 
 * can detect distance of an object up to 80cm. The specific IR sensor used in
 * the project is GP2Y0A21YK0F, and its member functions include reading
 * distance until a desired lower bound or upper bound is achieved.
 */
class SharpIR {
	public:
		SharpIR(const uint8_t _sensorType, uint8_t _sensorPin) : sensorType(_sensorType), pin(_sensorPin) {}
		uint8_t getDistance(bool avoidBurstRead = true);
		static const uint8_t GP2Y0A21YK0F = 1;
		void senseInboundBlockUpTo(uint8_t limit);
		void senseOutboundBlockUpTo(uint8_t limit);

	protected:
		uint8_t sensorType, pin;

	private:
		uint32_t lastTime = 0;
		uint32_t inboundTime = 10000; // 15seconds

};


#endif //SHARPIR_H