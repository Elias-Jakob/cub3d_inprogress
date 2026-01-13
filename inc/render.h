#ifndef RENDER_H
# define RENDER_H

# include <mlx.h>
# include <X11/keysym.h>

// init.c
bool	render(t_data *game);

// render.c
int	render_game(t_data *game);

// raycasting.c
double	raycasting(t_data *game, t_ray *ray);

// minimap.c
void	player_centered_minimap(t_data *game);
void	draw_minimap_ray(t_data *game, t_ray *ray, int wall_dist);

// hooks.c
int	key_hook(int key_code, t_data *game);
int	quit_game(t_data *game);

// utils.c
void	clean_up_mlx(t_data *game);
void	ft_put_pixel(t_img_data *image_data, int x, int y, int color);
unsigned long	get_timestamp(void);

int	create_trgb(int t, int r, int g, int b);

#endif
