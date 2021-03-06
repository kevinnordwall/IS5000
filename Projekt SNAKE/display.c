#include <pic32mx.h>
#include <stdlib.h>
#include <stdint.h>
#include "header.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)
#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)
#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)
#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)


/* delay:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases.
*/
void delay(int cyc) 
{
	int i;
	for(i = cyc; i > 0; i--);
}

void display_init(void) 
{
    DISPLAY_CHANGE_TO_COMMAND_MODE;
    delay(10);
    DISPLAY_ACTIVATE_VDD;
    delay(1000000);

    spi_send_recv(0xAE);
    DISPLAY_ACTIVATE_RESET;
    delay(10);
    DISPLAY_DO_NOT_RESET;
    delay(10);

    spi_send_recv(0x20);
    spi_send_recv(0x0);

    spi_send_recv(0x8D);
    spi_send_recv(0x14);

    spi_send_recv(0xD9);
    spi_send_recv(0xF1);

    DISPLAY_ACTIVATE_VBAT;
    delay(10000000);

    spi_send_recv(0xA1);
    spi_send_recv(0xC8);

    spi_send_recv(0xDA);
    spi_send_recv(0x20);

    spi_send_recv(0xAF);

    delay(10);
    DISPLAY_CHANGE_TO_DATA_MODE;
}

void spi_send_recv(uint8_t data) 
{
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
}

void pixel_update(uint8_t *pix) 
{
    int i;
    for (i = 0; i < 512; ++i)
        spi_send_recv(pix[i]);
}