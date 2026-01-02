#include "cub3d.h"

void	draw_wall2d(t_data *game, int x, int y, int color)
{
	int	wall_x;
	int	wall_y;
	int	offset_x = 0;
	int	offset_y = 0;

	wall_x = 0;
	while (wall_x < TILE_2D)
	{
		wall_y = 0;
		while (wall_y < TILE_2D)
		{
			if (wall_x != 0)
				offset_x = 1;
			if (wall_y != 0)
				offset_y = 1;
			ft_put_pixel(game->image, x*TILE_2D+wall_x-offset_x, y*TILE_2D+wall_y-offset_y, color);
			wall_y++;
			offset_x = 0;
			offset_y = 0;
		}
		wall_x++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	fill_ceil_and_floor(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2) // ceil
				ft_put_pixel(game->image, x, y, create_trgb(0, game->rgb.ceil[RED], game->rgb.ceil[GREEN], game->rgb.ceil[BLUE]));
			else
				ft_put_pixel(game->image, x, y, create_trgb(0, game->rgb.floor[RED], game->rgb.floor[GREEN], game->rgb.floor[BLUE]));
			y++;
		}
		x++;
	}
}

void	draw_map2d(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map.x)
	{
		y = 0;
		while (y < game->map.y)
		{
			if (game->map.arr[y][x] == '1')
				draw_wall2d(game, x, y, 0x8a8686);
			else
				draw_wall2d(game, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

void	draw_player(t_data *game)
{
	int	y;
	int	x;
	int	px;
	int	py;

	px = game->player->x * TILE_2D;
	py = game->player->y * TILE_2D;
	y = 0;
	while (y < 7)
	{
		x = 0;
		while (x < 7)
		{
			ft_put_pixel(game->image,
				px - 7 / 2 + x,
				py - 7 / 2 + y, 0xFFFF00);
			x++;
		}
		y++;
	}
	// direction
	ft_put_pixel(game->image, px, py, 0xFF0000);
	// draw direction line
	int	line_len = raycasting(game);//20;
	int	i = 1;
	while (i < line_len)
	{
		ft_put_pixel(game->image,
			(int)(px + game->player->dir_x * i),
			(int)(py + game->player->dir_y * i), 0xFF0000);
		i++;
	}

	// draw plane line
	// ft_put_pixel(game->image, px + TILE_2D / 2, py + TILE_2D / 2, 0xFFFFFF);
	// i = 1;
	// while (i < line_len)
	// {
	// 	ft_put_pixel(game->image,
	// 		px + TILE_2D / 2 + game->player->plane_x * i,
	// 		py + TILE_2D / 2 - game->player->plane_y * i, 0x0000FF);
	// 	ft_put_pixel(game->image,
	// 		px + TILE_2D / 2 - game->player->plane_x * i,
	// 		py + TILE_2D / 2 + game->player->plane_y * i, 0x0000FF);
	// 	i++;
	// }
}

void	render_game(t_data *game)
{
	fill_ceil_and_floor(game);
	// raycasting(game);
	draw_map2d(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
}
