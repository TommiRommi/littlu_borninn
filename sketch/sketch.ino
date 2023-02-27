#ifndef ARDUINO
#error þú verður að nota arduino compiler
#else

#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>
#include <stdbool.h>
#include <pins.h>
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

/* pins */
#define echo_pin 	p2
#define ena_pin 	p3
#define trig_pin 	p4
#define led_pin	p7
#define servo_pin	p8
#define in1_pin	p12
#define in2_pin	p13

/* timing */
#define SERVO_SPEED		500
#define SERVO_LOOP_COUNT	6
#define DC_SPIN_AMOUNT		SERVO_LOOP_COUNT >> 1

/* distance */
#define SERVO_ANGLE	90
/* sensor */
#define DISTANCE	2000

const uint8_t pin_call_order[] PROGMEM = {
	4, 7, 3, 12, 13
};

auto on 	= HIGH;
auto off 	= LOW;


SoftwareSerial mySoftwareSerial(10, 11);

class skeleton_baby : public Servo, public DFRobotDFPlayerMini
{
private:
	void record_motion();
public:
	inline void robot_move();	
};


void skeleton_baby::record_motion()
{
	digitalWrite(in2_pin, off);

	while(true)
	{
		digitalWrite(trig_pin, off);
		delayMicroseconds(5);
		digitalWrite(trig_pin, on);
		delayMicroseconds(10);
		digitalWrite(trig_pin, off);

		digitalWrite(led_pin, off);

		uint16_t distance = pulseIn(echo_pin, on);
		if(distance < DISTANCE && distance != 0)
		{
			digitalWrite(led_pin, on);
			break;
		}
	}
}


inline void skeleton_baby::robot_move()
{
	mySoftwareSerial.begin(9600);

	/* all pinmodes */	
	pinMode(echo_pin, INPUT);	
	for(uint8_t x = 0; x < sizeof(pin_call_order); ++x)
	{
		pinMode(pin_call_order[x], OUTPUT);
	}

	// prevents the DC motor from spinning
	digitalWrite(in1_pin, off); 
	digitalWrite(in2_pin, off); 

	Servo::attach(servo_pin);

	while(!DFRobotDFPlayerMini::begin(mySoftwareSerial))

	DFRobotDFPlayerMini::volume(10);
	DFRobotDFPlayerMini::loop(1);

	while(true)
	{
		DFRobotDFPlayerMini::pause();
		record_motion();
		DFRobotDFPlayerMini::start();
		digitalWrite(led_pin, on);

		for(uint8_t x = 0; x < SERVO_LOOP_COUNT; ++x)
		{
			if(x == DC_SPIN_AMOUNT)
			{
				digitalWrite(in2_pin, on);
			}

			Servo::write(0);
			delay(SERVO_SPEED);
			Servo::write(SERVO_ANGLE);
			delay(SERVO_SPEED);
		}

		digitalWrite(led_pin, off);
	}

}


int main(void)
{
	reset();

	skeleton_baby baby;

	baby.robot_move();
}

/* öryggis kóði */
__asm__ __volatile__ (
	"loop:\n"
	"jmp loop\n"
);					

#endif
