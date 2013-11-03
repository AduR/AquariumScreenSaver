#ifndef FT_RENDER_H
#define FT_RENDER_H

void ft_render(t_surface *ptr[], t_surface *screen);
void ft_clear(t_surface *screen);
void ft_put_char_colored(char c, int attr, int fg, int bg);
void ft_update_pos(t_surface *ptr, unsigned int timer);

#endif /* FT_RENDER_H */
