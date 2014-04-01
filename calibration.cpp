/*
 * SPARK MAKER KIT - FACEBOOK LIKES ALERT (CALIBRATION)
 * =========================================================
 * Copy this into a new application at:
 * https://www.spark.io/build and go nuts!
 * !! WIRING info on line 15 below !!
 * ---------------------------------------------------------
 *  Author: BDub
 * Website: http://technobly.com
 *    Date: Mar 31st 2014
 * =========================================================
 * https://github.com/technobly/SparkCore-FacebookLikesAlert
 * 
 *
 * WIRING is so simple
 * -----------------------------
 * SERVO             SPARK CORE
 * Brown or Black  - GND
 * Red             - VIN (5V)
 * Orange or White - A7
 * -----------------------------
 */

/* ============================= INCLUDES ================================== */
#include "application.h"

/* === CHANGE THESE NUMBERS TO FIND WHAT SERVO DEGREE MAPS TO WHICH DIGIT == */
#define SERVO_DEG_0 39 // servo degree value to point to digit 0
#define SERVO_DEG_9 79 // servo degree value to point to digit 9

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

uint32_t startTime;
uint16_t likesNumber = 0;
uint8_t servoPos;

/* This function is called once at start up ---------------------------------*/
void setup()
{
	myservo.attach(A7);  // attaches servo to A7 pin to the servo object
	Serial.begin(115200); // open a serial terminal after your core boots...
	while(!Serial.available()) SPARK_WLAN_Loop(); // ... and press ENTER
	startTime = millis();
}

/* This function loops forever ----------------------------------------------*/
void loop()
{
	if(millis() - startTime < 1000UL)
		return;

	startTime = millis();
	// This will run in a loop converting to servo position, 
	// setting servo position and printing servo position to USB Serial
	// so we can map out our number scale.
	servoPos = map(likesNumber,0,9,38,79);
	myservo.write(servoPos); // tell servo to go to position in variable 'servoPos'
	Serial.print(likesNumber); Serial.print(" "); Serial.println(servoPos);
	if(++likesNumber > 9) likesNumber = 0;
}