#include "header.h"
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdlib.h>
#include <stdio.h>

uint8_t pixels[512];
uint8_t border[128][32];
int menu = 0;
int speed = 650000;
volatile int* portd = (volatile int*) 0xbf8860D0;

void configuration(void)
{
    /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;    /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;    /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
    
}

// void clear_screen(void) {
//     display_string(0,"");
//     display_string(1,"");
//     display_string(2,"");
//     display_string(3,"");
//     display_update();
// }

void draw_pixel(int x, int y) {
    int row = 0;
    if (y>0) {
        row = y/8;
    }
    pixels[row * 128 + x] |= 1 << (y - row * 8);
}

void erase_pixel(int x, int y) {
    int row = 0;
    if (y>0) {
        row = y/8;
    }
    pixels[row * 128 + x] &= ~( 1 << (y - row * 8));
}

void button_config(void)
{
	TRISDSET = 0xE0;
}

void main_screen(void)
{
    // display_string(0,"-----SNAKE------");
    // display_string(1," 1:PLAY         ");
    // display_string(2," 2:HIGHSCORE    ");
    // display_string(3," 3:SETTINGS     ");
    // display_update();
    
    while(1)
    {
        pixel_update(launch_screen);
        button_config();
        int buttons = get_buttons();
        if( menu != 0) return;
        if( buttons & 0x4 )
        {
            menu = 1;
        }
        if( buttons & 0x1 )
        {
            menu = 3;
        }
        
    }

}

void gameover_menu(void)
{
    while(1)
    {
        pixel_update(gameover_screen);
        int buttons = get_buttons();
        if( menu != 2) return;
        if( buttons & 0x2 )
        {
            menu = 0;
        }
    }
}

void settings_menu(void)
{
    while(1)
    {
        pixel_update(settings_screen);
        int buttons = get_buttons();
        if( menu != 3) return;
        if( buttons & 0x4 )
        {
            menu = 0;
        }
    }
}

void game_reset(void) {
    int i,j,k;
    pixel_update(pixels);

    for (i = 0; i < 512; ++i) {
        pixels[i] = 0;
    }

    for (j = 0;j<127;j++) {
        for (k = 0;k<31;k++) {
            border[j][k] = 0;
            // erase_pixel(j,k);
        }
    }

    pixel_update(pixels);
}

void start(uint8_t * pix)
{
    int old_choice = 1337;
    int buttons;
    while(1)
    {
        pixel_update(pix);
        PORTD;
        if( get_buttons() != 0 )
        {
            while( old_choice == get_buttons() );
        }
        if (menu == 0)
        {
            pix = launch_screen;
            pixel_update(pix);
            do
            {
                buttons = get_buttons();
            } while (buttons == 0);
            if( buttons & 0x4 )
            {
                game_main();
                menu = 2;
            }
            else if( buttons & 0x1 )
            {
                menu = 1;
                pix = settings_screen;
            }
            old_choice = buttons;
            buttons = 0;
            
        }
        else if( menu == 1 )
        {
            pix = settings_screen;
            pixel_update(pix);
            do
            {
                buttons = get_buttons();
            } while (buttons == 0);
            if( buttons & 0x4 ) // HIGH SPEED
            {
                menu = 0;
                pix = launch_screen;
                speed = 450000;
                // andra konstant
                // och tillbaka till launchscreen
            }
            else if ( buttons & 0x2 ) 
            {
                menu = 0;
                pix = launch_screen;
                speed = 650000;
            } // LOW SPEED
            old_choice = buttons;
            buttons = 0;
        }
        if( menu == 2)
        {
            pix = gameover_screen;
            pixel_update(pix);
            pixel_update(pix);
            do
            {
                buttons = get_buttons();
            } while (buttons == 0);
            if( buttons & 0x2 )
            {
                menu = 0;
                pix = launch_screen;
            }
            old_choice = buttons;
            buttons = 0;
        }
        
    }
}


int main(void)
{
    configuration();
    display_init();
    // timer();
    button_config();
    start(launch_screen);    
}