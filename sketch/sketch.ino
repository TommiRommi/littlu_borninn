#ifndef ARDUINO
#error þú verður að nota arduino compiler
#else

#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>
#include <pins.h>

/* echo = p2, trig = p3, led_pin = p4 */
#define echo_pin 	p2
#define trig_pin 	p3
#define led_pin		p4
#define servo_pin	p5

/* timing */
#define SERVO_SPEED		300
#define SERVO_LOOP_COUNT	10

Servo servo_p;


inline void record_motion()
{
	while(true)
	{	
		digitalWrite(trig_pin, LOW);
		delayMicroseconds(5);
		digitalWrite(trig_pin, HIGH);
		delayMicroseconds(10);
		digitalWrite(trig_pin, LOW);
		 
		pinMode(echo_pin, INPUT);		
		digitalWrite(led_pin, LOW);

		if(pulseIn(echo_pin, HIGH) < 2920)
		{
			digitalWrite(led_pin, HIGH);
			break;
		}
	}

}


int main(void)
{
	reset();

	pinMode(trig_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
	pinMode(led_pin, OUTPUT);

	servo_p.attach(servo_pin);

	while(true)
	{
		record_motion();
		digitalWrite(led_pin, HIGH);

		for(uint8_t x = 0; x < SERVO_LOOP_COUNT; x++)
		{
			servo_p.write(180);
			delay(SERVO_SPEED);
			servo_p.write(0);
			delay(SERVO_SPEED);
		}

		digitalWrite(led_pin, LOW);
	}
}

/* öryggis kóði */
#pragma GCC optimize ("O0")
__asm__ __volatile__ (
	"loop:\n"
	"jmp loop\n"
);					

#endif
