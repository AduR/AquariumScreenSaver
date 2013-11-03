#ifndef CONSTANTES_H
#define CONSTANTES_H

/* ENUM */
typedef enum    e_type
{
    E_TYPE_WAVE,
    E_TYPE_FISH,
    E_TYPE_BOAT,
    E_TYPE_CASTLE,
    E_TYPE_SEAWEED,
    E_TYPE_SHARK,
    E_TYPE_LAST
}               t_type;

/* STRUCT */
typedef struct  s_vector
{
    int x;
    int y;
}               t_vector;

typedef struct s_pxl
{
    char        c;
    int         fg;
    int         bg;
}               t_pxl;

typedef struct  s_surface
{
    t_pxl       **tab;
    t_vector    pos;
    t_vector    dim;
    int         speed;
    t_vector    initial_pos;
    t_type      type;
}               t_surface;

/* DEFINE */
#define FPS                 2

#define SCREEN_NB_LIGNE     40
#define SCREEN_NB_COLONNE   80

#define RESET       0
#define BRIGHT      1
#define DIM         2
#define UNDERLINE   3
#define BLINK       4
#define REVERSE     7
#define HIDDEN      8

#define BLACK       0
#define RED         1
#define GREEN       2
#define YELLOW      3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define WHITE       7

#endif /* CONSTANTES_H */
