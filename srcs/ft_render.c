/*******************************************************************************
*
*  File Name : ft_render.c
*
*  Purpose :
*
*  Creation Date : 10-10-13 18:12:12
*
*  Last Modified : 02-11-13 12:11:11
*
*  Created By :
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "constantes.h"
#include "ft_init.h"
#include "ft_graphics.h"

#include "ft_render.h"

void ft_render(t_surface *ptr[], t_surface *screen)
{
    int x;

    ft_clear(screen);
    for (x = 0; x < E_TYPE_LAST; x++)
        ft_blit(ptr[x], screen, ptr[x]->pos.x, ptr[x]->pos.y);

    ft_flip(screen);
}

void ft_clear(t_surface *screen)
{
    int x, y;

    for (y = 0; y < screen->dim.y; y++)
    {
        for (x = 0; x < screen->dim.x; x++)
        {
            screen->tab[y][x].c = ' ';
            screen->tab[y][x].bg = BLACK;
            screen->tab[y][x].fg = WHITE;
        }
    }
}

void ft_put_char_colored(char c, int attr, int fg, int bg)
{
    char command[15];

    sprintf(command, "\x1b[%d;%d;%dm", attr, fg + 30, bg + 40);
    printf("%s", command);
    if (c != 0)
        printf("%c", c);
}

void ft_update_pos(t_surface *ptr, unsigned int timer)
{
    if (ptr->speed != 0)
    {
        int dir = (ptr->speed < 0 ? -1 : 1);
        int speed_abs = ptr->speed * (ptr->speed < 0 ? -1 : 1);

        if (timer % speed_abs == 0)
            ptr->pos.x += dir;

        /* auto reseting wave */
        if (ptr->pos.x >= 0 && ptr->type == E_TYPE_WAVE)
            ptr->pos.x = -SCREEN_NB_COLONNE;
    }
}

