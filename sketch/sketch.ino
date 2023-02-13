#ifndef ARDUINO
#error þú verður að nota arduino compiler
#else

#include <Arduino.h>
#include <stdint.h>
#include <pins.h>

// echo = p2
// trig = p3
#define echo_pin p2
#define trig_pin p3


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
		digitalWrite(p4, LOW);

		if(pulseIn(echo_pin, HIGH) < 2920)
		{
			digitalWrite(p4, HIGH);
			break;
		}
	}

}


int main(void)
{
	reset();

	pinMode(trig_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
	pinMode(p4, OUTPUT);

	while(true)
	{
		record_motion();
		digitalWrite(p4, HIGH);
		delay(4000);
		digitalWrite(p4, LOW);
	}

	for(;;){}
	return(0);
}

#endif
