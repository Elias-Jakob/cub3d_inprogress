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
	double	wall_dist;
	t_ray	ray;
	int	color;

	for (int x = 0; x < WIDTH; x++)
	{
		ray.col = x;
		wall_dist = raycasting(game, &ray);
		draw_minimap_ray(game, &ray, (int)(wall_dist * game->tile_size));
		for (int y = 0; y < HEIGHT / wall_dist; y++)
		{
			color = 0x87CEEB;
			if (ray.side)
				color = 0xFFFFC5;
			if (x > MINIMAP_SIZE || HEIGHT / 2 - y > MINIMAP_SIZE) // dont overwrite the minimap
				ft_put_pixel(game->image, x, HEIGHT / 2 - y, color);
			ft_put_pixel(game->image, x, HEIGHT / 2 + y, color);
		}
	}
}

void	render_game(t_data *game)
{
	fill_backgrounds(game);
	player_centered_minimap(game);
	draw_rays(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
}
