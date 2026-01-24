#include "cub3d.h"

void	clean_up_mlx(t_data *game)
{
	int	i_tex;

	if (game->image->img)
		mlx_destroy_image(game->mlx, game->image->img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	i_tex = 0;
	while (i_tex < N_TEXTURES && game->text[i_tex].image.img)
		mlx_destroy_image(game->mlx, game->text[i_tex++].image.img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	angle_to_vector(t_player *player)
{
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}

unsigned long	get_timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_put_pixel(t_img_data *image_data, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
    	return;

	pixel = image_data->addr + (y * image_data->line_length + x
		* (image_data->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	draw_tile_line(t_data *game, t_minimap *map, int x)
{
	while (x < map->x1 && x <= MINIMAP_SIZE)
		ft_put_pixel(game->image, x++, map->y0, map->tile_color);
	if (x < MINIMAP_SIZE)
		ft_put_pixel(game->image, x, map->y0, MINIMAP_GRID_COLOR);
}
