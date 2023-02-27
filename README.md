# Littlu Börninn
## gott að vita
setup.sh mun skipta út mjög mikilvægum librarys og luna scripts til að þetta virki.
## arduino-cli
notaðu <a href="https://arduino.github.io/arduino-cli/">arduino-cli</a> til að compila og uploada forritið á unoinn.

Þegar að `arduino-cli` er set up þarftu að setja up `avr` fyrir `arv-g++` C++ compilerinn sem er notaður til að compila forritið fyrir unoinn.

`avr` getur verið set up með,
```sh
arduino-cli core install arduino:avr
```
hægt er að sannræna að `avr` er set up með,
```sh
arduino-cli core list
```
og útkoman ætti að vera svippuð þessu.
```
ID          Installed Latest Name              
arduino:avr 1.8.6     1.8.6  Arduino AVR Boards
```
þessi þrjú library þurfa að vera installuð. Til að installa þau skaltu
```sh
arduino-cli lib install servo
arduino-cli lib install DFRobotDFPlayerMini
```
## Compiling og Uploading
Áður en að þú compilar C++ forritið skaltu passa að <a href="https://www.gnu.org/software/make/">GNU make</a> sé til.

Passaðu það að notandinn þinn hefur leif til að skrifa í serial `character special file` sem er búið til frá því að stínga unoinum í samband.

Það er hægt að skoða hver hann file er með því að skrifa,
```sh
arduino-cli board list
```
```
Port         Protocol Type              Board Name  FQBN            Core       
/dev/ttyACM0 serial   Serial Port (USB) Arduino Uno arduino:avr:uno arduino:avr
------------
```
maður gefur notandanum læfi með a skrifa.
```sh
sudo chown $USER </path/to/serial/port>
```
Í lokinn keyrir þú `setup.sh` til að Compila og Uploada. (Passaðu að setup.sh er keyrt í sama directory og það er í)
```sh
chmod +x setup.sh && ./setup.sh </path/to/serial/port>
```
## Kóði
<details>
    <summary>ýttu á til að sjá kóða</summary>

```c++
#ifndef ARDUINO
#error þú verður að nota arduino compiler
#endif

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
#define servo_pin	p9
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
	4, 7, 3, 12, 13, 9
};

auto on 	= HIGH;
auto off 	= LOW;


SoftwareSerial mySoftwareSerial(10, 11);
Servo servo_p;
DFRobotDFPlayerMini dfrm;

inline void record_motion()
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


inline void robot_move()
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

	servo_p.attach(servo_pin);

	while(!dfrm.begin(mySoftwareSerial))

	dfrm.volume(10);
	dfrm.loop(1);

	while(true)
	{
		dfrm.pause();
		record_motion();
		dfrm.start();
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


int main(void)
{
	reset();
	robot_move();
}

/* öryggis kóði */
__asm__ __volatile__ (
	"loop:\n"
	"jmp loop\n"
);					
```
</details>

## myndir
<img src="/media/image/16762883544926591935683890084751.jpg" alt="mynd_1" width="300" height="400">
<img src="/media/image/16762883753051676671573604699100.jpg" alt="mynd_2" width="300" height="400"> 
<img src="/media/image/16762883952842121450982368944318.jpg" alt="mynd_3" width="300" height="400">
<img src="/media/image/16762884064637789580737797868149.jpg" alt="mynd_4" width="300" height="400">
<img src="/media/image/16762979306115285682871802955081.jpg" alt="mynd_5" width="300" height="400">
