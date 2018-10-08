#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void)
{
	// Use PORTD to get the value in Port D.
	// Get the bits 11 to 8
	// SW4 - 11, etc...
	// 1111 0000 0000
	// 0xf00
	// Return 0x4321
	int switches = (PORTD & 0xf00) >> 8;

	return switches;
}

int getbtns(void)
{
	// 1110 0000
	// 0xe0
	int buttons = (PORTD & 0xe0) >> 5;
	return buttons;
}