#ifndef HELPER_H
#define HELPER_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <pic32mx.h>

enum Direction {LEFT, RIGHT, UP, DOWN};
typedef struct {
    int x, y, length;
    enum Direction direction;
} Snake;

typedef struct node {
    int val;
    struct node * next;
} node_t;

extern int menu;
extern int speed;
extern uint8_t mode[512];
extern uint8_t pixels[512];
extern uint8_t border[128][32];
extern uint8_t launch_screen[512];
extern uint8_t gameover_screen[512];
extern uint8_t settings_screen[512];

void configuration(void);
void display_init(void);
void pixel_update(uint8_t *pix);
void erase_pixel(int x, int y);
void spi_send_recv(uint8_t data);
int get_buttons(void);
void delay(int cyc);

#endif