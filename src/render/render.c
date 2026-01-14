#include "cub3d.h"

static void	fill_backgrounds(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x <= MINIMAP_SIZE && y <= MINIMAP_SIZE)
				ft_put_pixel(game->image, x, y, MINIMAP_BG_COLOR);
			else if (y < HEIGHT / 2)
				ft_put_pixel(game->image, x, y, create_trgb(0, game->rgb.ceil[RED], game->rgb.ceil[GREEN], game->rgb.ceil[BLUE]));
			else
				ft_put_pixel(game->image, x, y, create_trgb(0, game->rgb.floor[RED], game->rgb.floor[GREEN], game->rgb.floor[BLUE]));
			x++;
		}
		y++;
	}
}

static void	draw_rays(t_data *game)
{
	t_ray	ray;
	t_column	col;

	col.x = 0;
	while (col.x < WIDTH)
	{
		raycasting(game, &ray, col.x);
		draw_minimap_ray(game, &ray);
		draw_texture_line(game, &ray, &col);
		col.x++;
	}
}

int	render_game(t_data *game)
{
	game->last_time_rendered = get_timestamp();
	fill_backgrounds(game);
	player_centered_minimap(game);
	draw_rays(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
	return (0);
}
