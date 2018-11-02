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

int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";
volatile int* porte = (volatile int*) 0xbf886110;
int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	*porte = (int) 0x0;

	// C
	// Create volatile pointer that points to address of TRISE (0xbf886100)
	// Change bits 7 to 0 to 0, which sets the 8 bits to output for Port E
	// DO NOT change the other bits at the address of TRISE
	volatile int* trise =(volatile int*) 0xbf886100;
	int maskE = 0xffffff00;
	*trise = *trise & maskE;
	


	// F
	// Create volatile pointer that points to address of TRISD using the definitions used in pic32mx.h
	// Change bits 11 to 5 to 1, which sets the 7 bits to input for Port D
	// DO NOT change the other bits at the address of TRISD
	// 0000 0000 0000 0000 0000 1111 1110 0000
	int maskD = 0xfe0;
	TRISD |= maskD;
	

	// Assignment 2
	PR2 = 31250; // 80MHz / 256 / 10	to get under 60k
	T2CONSET = 0x70; // Init T2CON to prescaling 1:256, bits 6-4 to 111
	T2CONSET = 0x8000; // Starts the timer, 1000 0000 0000 0000

}

/* This function is called repetitively from the main program */
void labwork( void )
{
	// Highest possible value for 16-bits: 65535
	// Lastly iterate value of Port E by 1
	int buttons = getbtns( );
	int switches = getsw( );
	if( (buttons & 0x4) )
	{
		mytime &= 0x0fff; // Set byte 4 to 0 in mytime with bitwise and
		mytime |= ( switches << 12 ); // Move switch bits 12 bits left, place switch values into mytime using bitwise or
	}

	if( (buttons & 0x2) )
	{
		mytime &= 0xf0ff;
		mytime |= ( switches << 8 );
	}

	if( (buttons & 0x1) )
	{
		mytime &= 0xff0f;
		mytime |= ( switches << 4 );
	}

	if( IFS(0) & 0x100 )
	{
		timeoutcount++;
		IFSCLR(0) = 0x100;
	}


	if ( timeoutcount == 10 )
	{
		time2string( textstring, mytime );
		display_string( 3, textstring );
		display_update();
		tick( &mytime );
		*porte = *porte + 1;
		timeoutcount = 0;
	}

  	display_image(96, icon);
	
}
