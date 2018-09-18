#include <stdlib.h>
#include <stdio.h>

int main()
{

	int z = 0xABCDEFFF;
	int x = 0xCCCCCCCC;
	int y = 0xDDDDDDDD;
	printf("%x\n", z); 

	z = ( z & 0xFFFFFF00 ) 
		| ((x & 0x1F000) >> 12) 
		| (( y & 0x7 ) << 5 );
	printf("%x\n", z); 
	return 0;
}

