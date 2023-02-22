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
arduino-cli lib install SoftwareSerialTX
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
```
</details>
