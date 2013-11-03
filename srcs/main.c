/*******************************************************************************
*
*  File Name : main.c
*
*  Purpose :
*
*  Creation Date : 10-10-13 18:12:12
*
*  Last Modified : 02-11-13 12:18:20
*
*  Created By :
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "constantes.h"
#include "ft_init.h"
#include "ft_render.h"
#include "ft_graphics.h"

int main(void)
{
    unsigned int timer = 0, x;
    t_surface *elem[E_TYPE_LAST];
    t_surface *screen;

    srand(42);
    screen = ft_init_screen();
    elem[0] = ft_init_wave();
    elem[1] = ft_load_surface("data/fish.ass", E_TYPE_FISH);
    elem[2] = ft_load_surface("data/whale.ass", E_TYPE_BOAT);
    elem[3] = ft_load_surface("data/castle.ass", E_TYPE_CASTLE);
    elem[4] = ft_load_surface("data/seaweed.ass", E_TYPE_SEAWEED);
    elem[5] = ft_load_surface("data/shark.ass", E_TYPE_SEAWEED);

    while (timer < FPS*60)
    {
        for (x = 0; x < E_TYPE_LAST; x++)
            ft_update_pos(elem[x], timer);

        ft_render(elem, screen);

        usleep(1000*1000/FPS);
        timer ++;
    }

    for (x = 0; x < E_TYPE_LAST; x++)
        ft_free_surface(elem[x]);
    ft_free_surface(screen);
    ft_put_char_colored(0, RESET, WHITE, BLACK);

    return 0;
}
