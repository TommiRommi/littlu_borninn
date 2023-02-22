#ifndef ARDUINO
#error þú verður að nota arduino compiler
#else

#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>
#include <stdbool.h>
#include <pins.h>

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
#define SERVO_ANGLE	60
/* sensor */
#define DISTANCE	2000

const uint8_t pin_call_order[] PROGMEM = {
	4, 7, 3, 12, 13
};

auto on 	= HIGH;
auto off 	= LOW;

Servo const servo_p;


template<typename T>
T record_motion()
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
		if(pulseIn(echo_pin, on) < DISTANCE)
		{
			digitalWrite(led_pin, on);
			break;
		}
	}
}


int main(void)
{
	reset();

	/* pinmodes */
	pinMode(echo_pin, INPUT);	

	for(uint8_t x = 0; x < sizeof(pin_call_order); ++x)
	{
		pinMode(pin_call_order[x], OUTPUT);
	}

	digitalWrite(in1_pin, off); 
	digitalWrite(in2_pin, off); 

	servo_p.attach(servo_pin);

	while(true)
	{
		record_motion<void>();
		digitalWrite(led_pin, on);

		for(uint8_t x = 0; x < SERVO_LOOP_COUNT; ++x)
		{
			if(x == DC_SPIN_AMOUNT)
			{
				digitalWrite(in2_pin, on);
			}

			servo_p.write(SERVO_ANGLE);
			delay(SERVO_SPEED);
			servo_p.write(0);
			delay(SERVO_SPEED);
		}

		digitalWrite(led_pin, off);
	}
}

/* öryggis kóði */
__asm__ __volatile__ (
	"loop:\n"
	"jmp loop\n"
);					

#endif
