#include "../../inc/cub3d.h"

void	draw_wall2d(t_data *game, int x, int y, int color)
{
	int	wall_x;
	int	wall_y;
	int	offset_x = 0;
	int	offset_y = 0;
	
	wall_x = 0;
	while (wall_x < 32)
	{
		wall_y = 0;
		while (wall_y < 32)
		{
			if (wall_x != 0)
				offset_x = 1;
			if (wall_y != 0)
				offset_y = 1;
			ft_put_pixel(game->image, x*32+wall_x-offset_x, y*32+wall_y-offset_y, color);
			wall_y++;
			offset_x = 0;
			offset_y = 0;
		}
		wall_x++;
	}
}

void	fill_background(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ft_put_pixel(game->image, x, y, 0x000000);
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
	while (x < game->map_width)
	{
		y = 0;
		while (y < game->map_heigth)
		{
			if (game->map[y][x] == '1')
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
	
	y = 0;
	while (y < 7)
	{
		x = 0;
		while (x < 7)
		{
			ft_put_pixel(game->image,
				game->player->x - 7 / 2 + x,
				game->player->y - 7 / 2 + y, 0xFFFF00);
			x++;
		}
		y++;
	}
	// direction
	ft_put_pixel(game->image, game->player->x, game->player->y, 0xFF0000);
	// draw line
	int	line_len = 10;
	int	i = 1;
	while (i < line_len)
	{
		ft_put_pixel(game->image,
			(int)(game->player->x + game->player->dir_x * i),
			(int)(game->player->y - game->player->dir_y * i), 0xFF0000);
		i++;
	}
}

void	render_game(t_data *game)
{
	fill_background(game);
	draw_map2d(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
}
