/*******************************************************************************
*
*  File Name : ft_init.c
*
*  Purpose :
*
*  Creation Date : 10-10-13 18:12:12
*
*  Last Modified : 01-11-13 22:06:05
*
*  Created By :
*
*******************************************************************************/

#include <stdlib.h>
#include "constantes.h"

#include "ft_init.h"

t_surface *ft_init_wave(void)
{
    int x, y;
    int wave_length = 0, wave_or_not_wave = 0;
    t_surface *ptr;

    /* init - malloc */
    ptr = malloc(sizeof(t_surface));
    ptr->dim.x = SCREEN_NB_COLONNE * 2;
    ptr->dim.y = 4;

    ptr->tab = malloc(sizeof(t_pxl*) * ptr->dim.y);
    for (y = 0; y < ptr->dim.y; y++)
    {
        ptr->tab[y] = malloc(sizeof(t_pxl) * ptr->dim.x);
    }

    /* fill */
    for (y = 0; y < ptr->dim.y; y++)
    {
        for (x = 0; x < ptr->dim.x; x++)
        {
            ptr->tab[y][x].bg = BLACK;
            ptr->tab[y][x].fg = CYAN;

            if (y == 0)
                ptr->tab[y][x].c = '~';
            else
            {
                if (wave_length == 0)
                {
                    wave_length = rand()%10 + 4;
                    wave_or_not_wave++;
                }
                if (wave_or_not_wave % 2)
                    ptr->tab[y][x].c = '~';
                else
                    ptr->tab[y][x].c = ' ';
                wave_length--;
            }
        }
    }

    ptr->speed = 1;
    ptr->type = E_TYPE_WAVE;
    ptr->pos.x = -SCREEN_NB_COLONNE;
    ptr->pos.y = 6;

    return ptr;
}

t_surface *ft_init_screen(void)
{
    int x, y;
    t_surface *screen;

    screen = malloc(sizeof(t_surface));

    screen->dim.x = SCREEN_NB_COLONNE;
    screen->dim.y = SCREEN_NB_LIGNE;
    screen->tab = malloc(sizeof(t_pxl*) * screen->dim.y);

    for (y = 0; y < SCREEN_NB_LIGNE; y++)
    {
        screen->tab[y] = malloc(sizeof(t_pxl) * screen->dim.x);

        for (x = 0; x < SCREEN_NB_COLONNE; x++)
        {
            screen->tab[y][x].c = ' ';
            screen->tab[y][x].fg = WHITE;
            screen->tab[y][x].bg = BLACK;
        }
    }

    return screen;
}

