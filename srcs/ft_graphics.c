/*******************************************************************************
*
*  File Name : ft_graphics.c
*
*  Purpose :
*
*  Creation Date : 18-10-13 19:16:20
*
*  Last Modified : 22-10-13 17:07:44
*
*  Created By :
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "constantes.h"
#include "ft_render.h"
#include "ft_errors.h"

#include "ft_graphics.h"

#define BUF_SIZE    (200*100*3)

t_surface *ft_create_surface(t_vector dim)
{
    t_surface *ptr;
    int j;

    ptr = malloc(sizeof(t_surface));
    ptr->dim.x = dim.x;
    ptr->dim.y = dim.y;

    ptr->tab = malloc(sizeof(t_pxl*) * ptr->dim.y);
    for (j = 0; j < ptr->dim.y; j++)
        ptr->tab[j] = malloc(sizeof(t_pxl) * ptr->dim.x);

    return ptr;
}

void ft_get_file_to_str(char *path, char *buffer)
{
    int fd, ret;
    char str_error[100];

    /* open */
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        sprintf(str_error, "open() : %s", path);
        ft_print_error(__func__, __LINE__, str_error);
    }

     /* read */
    ret = read(fd, buffer, BUF_SIZE);
    if (ret <= 0)
    {
        sprintf(str_error, "read() : %s", path);
        ft_print_error(__func__, __LINE__, str_error);
    }
    buffer[ret] = '\0';

    close(fd);
}

void ft_check_file(char *path, char *str, t_vector *dim, t_vector *pos,
                    int *speed)
{
    int i = 0, j = 0;
    char str_error[100];

    /* init */
    sscanf(str, "%d", &dim->y);
    while (*str != ' ')
        str++;
    str++;
    sscanf(str, "%d", &dim->x);
    while (*str != ' ')
        str++;
    str++;
    sscanf(str, "%d", &pos->y);
    while (*str != ' ')
        str++;
    str++;
    sscanf(str, "%d", &pos->x);
    while (*str != ' ')
        str++;
    str++;
    sscanf(str, "%d", speed);
    while (*str != '\n')
        str++;
    str++;

    /* check */
    while (*str != 'o' && *(str+1) != 'k' && *(str+2) != '\0')
    {
        if (*str == '\n')
        {
            if (i != dim->x*3)
            {
                sprintf(str_error, "erreur parsing x : %s : have %d instead"
                        " of %d (y==%d)", path, i, dim->x, j);
                ft_print_error(__func__, __LINE__, str_error);
            }
            j++;
            i = 0;
        }
        else
            i++;
        str++;
    }
    if (j != dim->y)
    {
        sprintf(str_error, "erreur parsing y : %s : have %d instead of %d",
                path, j, dim->y);
        ft_print_error(__func__, __LINE__, str_error);
    }
}

t_surface *ft_load_surface(char *path, t_type type)
{
    t_vector pos, dim;
    int speed;
    char *buffer;
    t_surface *surface;

    buffer = malloc(sizeof(char) * BUF_SIZE);
    ft_get_file_to_str(path, buffer);
    ft_check_file(path, buffer, &dim, &pos, &speed);
    surface = ft_create_surface(dim);
    ft_fill_surface(surface, buffer);

    surface->pos.x = pos.x;
    surface->pos.y = pos.y;
    surface->speed = speed;
    surface->type = type;

    free(buffer);
    return surface;
}

void ft_fill_surface(t_surface *surface, char *buffer)
{
    int x = 0, y = 0, i = 0;

    while (*buffer != '\n')
        buffer++;
    buffer++;

    while (buffer[i] != 'o' && buffer[i+1] != 'k' && buffer[i] != '\0'
            && x <= surface->dim.x && y < surface->dim.y)
    {
        if (buffer[i] == '\n')
        {
            y++;
            x = 0;
            i++;
        }
        else
        {
            surface->tab[y][x].c = buffer[i];
            surface->tab[y][x].fg = buffer[i+1] - '0';
            surface->tab[y][x].bg = buffer[i+2] - '0';
            i += 3;
            x++;
        }
    }
}

void ft_blit(t_surface *src, t_surface *dest, int x, int y)
{
    int i, j;

    for (j = 0; j < src->dim.y; j++)
    {
        for (i = 0; i < src->dim.x; i++)
        {
            if (y + j >= 0 && y + j < dest->dim.y
            && x + i >= 0 && x + i < dest->dim.x
            && src->tab[j][i].c != '\t')
            {
                dest->tab[y+j][x+i].c = src->tab[j][i].c;
                dest->tab[y+j][x+i].bg = src->tab[j][i].bg;
                dest->tab[y+j][x+i].fg = src->tab[j][i].fg;
            }
        }
    }
}



void ft_flip(t_surface *screen)
{
    int x, y;

    system("clear");

    printf("+");
    for (x = 0; x < screen->dim.x; x++)
        printf("-");
    printf("+\n");

    for (y = 0; y < screen->dim.y; y++)
    {
        printf("|");
        for (x = 0; x < screen->dim.x; x++)
        {
            /*printf("%d", x%10);*/
            ft_put_char_colored(screen->tab[y][x].c, RESET,
                            screen->tab[y][x].fg, screen->tab[y][x].bg);
        }
        ft_put_char_colored('|', RESET, WHITE, BLACK);
        printf("\n");
    }

    printf("+");
    for (x = 0; x < screen->dim.x; x++)
        printf("-");
    printf("+\n");
}

void ft_free_surface(t_surface *ptr)
{
    int y;

    for (y = 0; y < ptr->dim.y; y++)
        free(ptr->tab[y]);
    free(ptr->tab);
    free(ptr);
    ptr = NULL;
}

