#ifndef FT_GRAPHICS_H
#define FT_GRAPHICS_H

t_surface *ft_create_surface(t_vector dim);

t_surface *ft_load_surface(char *path, t_type type);
void ft_get_file_to_str(char *path, char *buffer);
void ft_check_file(char *path, char *str, t_vector *dim, t_vector *pos,
                    int *speed);
void ft_fill_surface(t_surface *surface, char *buffer);

void ft_blit(t_surface *src, t_surface *dest, int x, int y);
void ft_flip(t_surface *screen);
void ft_free_surface(t_surface *ptr);

#endif /* FT_GRAPHICS_H */
