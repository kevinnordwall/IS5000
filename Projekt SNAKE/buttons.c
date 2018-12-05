#include <pic32mx.h>
#include <stdlib.h>

int get_buttons(void)
{
	// 1110 0000
	// 0xe0
	int buttons = (PORTD & 0xe0) >> 5;
	return buttons;
}