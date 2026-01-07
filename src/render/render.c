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

/* WORK IN PROGRESS
void	player_centered_minimap(t_data *game)
{
	t_minimap	map;
	int	tile_ratio;
	int	y;
	int	x;

	// Background
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			ft_put_pixel(game->image, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	tile_ratio = MINIMAP_SIZE / TILE_2D;
	// TODO: What if these values are out of range?
	map.start_col = game->player->x - tile_ratio / 2;
	map.start_row = game->player->y - tile_ratio / 2;
	map.end_col = game->player->x + tile_ratio / 2;
	map.end_row = game->player->y + tile_ratio / 2;
	// TODO: init map width and height @ patrick
	printf("%d %d\n", game->map_height, game->map_width);
	game->map_height = 8;
	map.y = map.start_row;
	if (game->map_height < map.end_row)
		map.end_row = game->map_height;
	while (map.y < map.end_row)
	{
		map.x = map.start_col;
		while (map.x < map.end_col)
		{
			if (map.y < 0 || map.x < 0
				|| map.y >= game->map_height || (size_t)map.x >= ft_strlen(game->map.arr[map.y]))
			{
				map.x++;
				continue ;
			}
			if (game->map.arr[map.y][map.x] == '1')
				draw_wall2d(game, map.x - map.start_col, map.y - map.start_row, 0x8a8686);
			else
				draw_wall2d(game, map.x - map.start_col, map.y - map.start_row, 0x000000);
			map.x++;
		}
		map.y++;
	}
	// t_ray	ray;
	// double	wall_dist;

	y = 0;
	while (y < 7)
	{
		x = 0;
		while (x < 7)
		{
			ft_put_pixel(game->image,
				MINIMAP_CENTER - 4 + x + TILE_2D / 2,
				MINIMAP_CENTER - 4 + y + TILE_2D / 2, 0xFFFF00);
			x++;
		}
		y++;
	}
}
*/

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
	t_ray	ray;
	double	wall_dist;

	px = game->player->x * TILE_2D;
	py = game->player->y * TILE_2D;
	y = 0;
	while (y < 7)
	{
		x = 0;
		while (x < 7)
		{
			ft_put_pixel(game->image,
				px - 3 + x,
				py - 3 + y, 0xFFFF00);
			x++;
		}
		y++;
	}
	// direction
	ft_put_pixel(game->image, px, py, 0xFF0000);
	// draw direction line
	
	for (int x = 0; x < WIDTH; x++)
	{
		ray.col = x;
		wall_dist = raycasting(game, &ray) * TILE_2D;
		int	i = 0;
		while (i < (int)wall_dist)
		{
			ft_put_pixel(game->image,
				(int)(px + ray.dir_x * i),
				(int)(py + ray.dir_y * i), 0xFF0000);
			i++;
		}
	}
}

void	draw_walls3d(t_data *game)
{
	double	wall_dist;
	t_ray	ray;
	int	color;

	for (int x = 0; x < WIDTH; x++)
	{
		ray.col = x;
		wall_dist = raycasting(game, &ray);
		for (int y = 0; y < HEIGHT / wall_dist; y++)
		{
			color = 0x87CEEB;
			if (ray.side)
				color = 0xFFFFC5;
			ft_put_pixel(game->image, x, HEIGHT / 2 + y, color);
			ft_put_pixel(game->image, x, HEIGHT / 2 - y, color);
		}
	}
}

void	render_game(t_data *game)
{
	fill_ceil_and_floor(game);
	draw_walls3d(game);
	// player_centered_minimap(game);
	draw_map2d(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
}
