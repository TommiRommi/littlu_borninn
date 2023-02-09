#ifndef ARDUINO
#error þú verður að nota arduino compiler
#else

#include <Arduino.h>
#include <stdint.h>

int main(void)
{
	reset();

	/* kóði kemur hér */

	for(;;){}
	return(0);
}

#endif
