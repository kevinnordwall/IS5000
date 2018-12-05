#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

// node_t * snake_xhead = NULL;
// node_t * snake_yhead = NULL;
int snake_x[512] = {0};
int snake_y[512] = {0};
int pixel_quantity;
Snake snake;

// Linked list helpers
// int remove_last(node_t * head) {
//     int retval = 0;
//     /* if there is only one item in the list, remove it */
//     if (head->next == NULL) {
//         retval = head->val;
//         free(head);
//         return retval;
//     }

//     /* get to the second to last node in the list */
//     node_t * current = head;
//     while (current->next->next != NULL) {
//         current = current->next;
//     }

//     /* now current points to the second to last item of the list, so let's remove current->next */
//     retval = current->next->val;
//     free(current->next);
//     current->next = NULL;
//     return retval;

// }

// void push(node_t ** head, int val) {
//     node_t * new_node;
//     new_node = malloc(sizeof(node_t));

//     new_node->val = val;
//     new_node->next = *head;
//     *head = new_node;
// }

// Sätter gränser för spelplan
void border_init(void)
{
    int k,l;
    for (k = 0;k<128;k++) {
        border[k][0]    = 1;
        border[k][31]   = 1;
    }

    for (l=0;l<31;l++) {
        border[0][l]    = 1;
        border[127][l]  = 1;
    }
}

void snake_init(Snake *snake)
{   
    (*snake).x = 32;
    (*snake).y = 10;
    (*snake).direction = RIGHT;
    (*snake).length = 12;
    int i;
    for( i = 0; i < (*snake).length; i++ ) 
    {
        snake_x[i] = 0;
        snake_y[i] = 0;
        erase_pixel(snake_x[i],snake_y[i]);
    }
    // pixel_quantity = 1;
}

void change_direc(Snake *snake, int btn_1, int btn_2)
{
    if( btn_1 )
    {
        if( (*snake).direction == UP ) (*snake).direction = LEFT;
        else if( (*snake).direction == DOWN ) (*snake).direction = RIGHT;
        else if( (*snake).direction == RIGHT ) (*snake).direction = UP;
        else if( (*snake).direction == LEFT ) (*snake).direction = DOWN;
    }
    else if ( btn_2 )
    {
        if( (*snake).direction == UP ) (*snake).direction = RIGHT;
        else if( (*snake).direction == DOWN ) (*snake).direction = LEFT;
        else if( (*snake).direction == LEFT ) (*snake).direction = UP;
        else if( (*snake).direction == RIGHT ) (*snake).direction = DOWN;
    }
}

void game_init(void)
{
    // Rita borders
    border_init();
    // Skapa orm
    snake_init(&snake);

    // Skapa mat
}

// void draw_snake(node_t * xhead, node_t * yhead)
// {
//     node_t * x_current = xhead;
//     node_t * y_current = yhead;
//     int i = 0;
//     while (x_current != NULL) {
//         int x = x_current->val;
//         int y = y_current->val;
//         draw_pixel(x,y);
//         if(i > 1)
//         {
//             border[x][y] = 1;
//         }
//         x_current = x_current->next;
//         y_current = y_current->next;
//         i++;
//     }
// }

void update_snake(Snake *snake)
{
    delay(speed);
    int x = (*snake).x;
    int y = (*snake).y;
    int length = (*snake).length;
    int i;

    if((*snake).direction == UP) y--;
    if((*snake).direction == DOWN) y++;
    if((*snake).direction == RIGHT) x++;
    if((*snake).direction == LEFT) x--;

    (*snake).x = x;
    (*snake).y = y;
    int first_tempx = snake_x[0];
    int first_tempy = snake_y[0];
    int sec_tempx;
    int sec_tempy;
    
    snake_x[0] = x;
    snake_y[0] = y;
    draw_pixel(x,y);
    // push ny position
    for( i = 1; i < length; i++ )
    {
        sec_tempx = snake_x[i];
        sec_tempy = snake_y[i];
        snake_x[i] = first_tempx;
        snake_y[i] = first_tempy;
        draw_pixel(first_tempx,first_tempy);
        first_tempx = sec_tempx;
        first_tempy = sec_tempy;
        border[snake_x[i]][snake_y[i]] = 1;
        // pixel_quantity++;
    }
    border[first_tempx][first_tempy] = 0;
    erase_pixel(first_tempx,first_tempy);

    // kollar om längden på ormen > snake.length
    // if( pixel_quantity > length )
    // {
    //     // om så är fallet pop
    //     int x_last = remove_last(snake_xhead);
    //     int y_last = remove_last(snake_yhead);
        
    //     pixel_quantity--;
    // }
    // rita
    // draw_snake(snake_xhead,snake_yhead);
    
}

void restart(void) {
    delay(3000000);
    pixel_update(pixels);
}


unsigned random_number()
{
   static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
   unsigned int b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27; 
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}

int food_coord()
{
    int food_x = random_number() % 125;
    int food_y = random_number() % 25;

    border[food_x][food_y] = 2;
    draw_pixel(food_x, food_y);
    return 1;
}

void game_main()
{
    int food = 0;
    restart();
    game_init();
    pixel_update(pixels);

    // btn_1 = BTN4
    // btn_2 = BTN3
    // btn_3 = BTN2
    while(1)
    {
        int buttons = get_buttons();
        int btn_1 =  buttons & 0x4;
        int btn_2 =  buttons & 0x2;
        int btn_3 =  buttons & 0x1;
        change_direc(&snake, btn_1, btn_2);
        // Uppdatera och rita ormen
        
        update_snake(&snake);
        pixel_update(pixels);
        
        


        if( btn_3 )
        {
            game_reset();
            snake_init(&snake);
            delay(1000);
            menu = 0;
            return;
        }

        // Kolla border och orm
        if( border[snake.x][snake.y] == 1 )
        {
            // G;r en gameover sk'rm
            game_reset();
            snake_init(&snake);
            delay(1000);
            menu = 2;
            return;
        }
        // Kolla mat
        if( border[snake.x][snake.y] == 2 )
        {
        
            border[snake.x][snake.y] = 0; 
            food = 0;
            // Ormen ska växa  
            snake.length += 2;
            
        }
        
        // Generera mat
        
        if ( food == 0 )
        {
            food = food_coord();
            pixel_update(pixels);
        }
        
    }
}