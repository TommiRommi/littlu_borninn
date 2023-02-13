#ifndef ARDUINO
#error þú verður að nota arduino compiler
#else

#include <Arduino.h>
#include <stdint.h>
#include <pins.h>

// echo = p2, trig = p3, led_pin = p4
#define echo_pin 	p2
#define trig_pin 	p3
#define led_pin		p4


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

	while(true)
	{
		record_motion();
		digitalWrite(led_pin, HIGH);
		delay(4000);
		digitalWrite(led_pin, LOW);
	}

	for(;;){}
	return(0);
}

#endif
