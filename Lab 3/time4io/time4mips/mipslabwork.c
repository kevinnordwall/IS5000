/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957; // Maybe change dis one??

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	// C
	// Create volatile pointer that points to address of TRISE (0xbf886100)
	// Change bits 7 to 0 to 0, which sets the 8 bits to output for Port E
	// DO NOT change the other bits at the address of TRISE

	// D
	// Create volatile pointer that points to address of TRISD using the definitions used in pic32mx.h
	// Change bits 11 to 5 to 1, which sets the 7 bits to input for Port D
	// DO NOT change the other bits at the address of TRISD
	
	return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
	// Create a volatile pointer that points to PORTE (0xbf886110)
	// Initiate value of Port E to 0
	// Lastly iterate value of Port E by 1
	delay( 1000 );
	time2string( textstring, mytime );
  	display_string( 3, textstring );
  	display_update();
  	tick( &mytime );
  	display_image(96, icon);
}
