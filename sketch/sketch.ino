#ifndef ARDUINO
#error you need to compile this with a arduino compiler
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
