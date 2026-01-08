#include "cub3d.h"

void	draw_wall2d(t_data *game, double x, double y, int color)
{
	int	px;
	int	py;
	int	wall_end_x;
	int	wall_end_y;
	int	y_start;

	px = floor(x * TILE_2D);
	py = floor(y * TILE_2D);
	wall_end_x = px + TILE_2D - 1;
	wall_end_y = py + TILE_2D - 1;
	y_start = py;
	while (px < wall_end_x && px < MINIMAP_SIZE)
	{
		while (py < wall_end_y && py < MINIMAP_SIZE)
		{
			if (wall_end_y < MINIMAP_SIZE)
				ft_put_pixel(game->image, px, wall_end_y, MINIMAP_GRID_COLOR);
			if (wall_end_x < MINIMAP_SIZE)
				ft_put_pixel(game->image, wall_end_x, py, MINIMAP_GRID_COLOR);
			ft_put_pixel(game->image, px, py, color);
			py++;
		}
		py = y_start;
		px++;
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
			ft_put_pixel(game->image, x, y, 0x00000);
			x++;
		}
		y++;
	}
	tile_ratio = MINIMAP_SIZE / TILE_2D;
	// TODO: What if these values are out of range?
	map.start_col = (int)game->player->x - tile_ratio / 2;
	map.start_row = (int)game->player->y - tile_ratio / 2;
	map.end_col = (int)game->player->x + tile_ratio / 2 + 1;
	map.end_row = (int)game->player->y + tile_ratio / 2 + 1;
	// TODO: init map width and height @ patrick
	printf("%d %d\n", game->map_height, game->map_width);
	game->map_height = 8;
	map.y = map.start_row;
	if (game->map_height < map.end_row)
		map.end_row = game->map_height;
	double	x_fract = game->player->x - (int)game->player->x;
	double	y_fract = game->player->y - (int)game->player->y;
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
				draw_wall2d(game, (map.x - map.start_col) - x_fract, (map.y - map.start_row) - y_fract, 0xFFFFFF);
			else
				draw_wall2d(game, (map.x - map.start_col) - x_fract, (map.y - map.start_row) - y_fract, 0x000000);
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
				MINIMAP_CENTER - 3 + x,
				MINIMAP_CENTER - 3 + y, 0xFFFF00);
			x++;
		}
		y++;
	}
	t_ray	ray;
	double	wall_dist;
	// draw direction line
	
	for (int x = 0; x < WIDTH; x++)
	{
		ray.col = x;
		wall_dist = raycasting(game, &ray) * TILE_2D;
		int	i = 0;
		while (i < (int)wall_dist
			&& MINIMAP_CENTER + ray.dir_x * i < MINIMAP_SIZE
			&& MINIMAP_CENTER + ray.dir_y * i < MINIMAP_SIZE)
		{
			ft_put_pixel(game->image,
				(int)(MINIMAP_CENTER + ray.dir_x * i),
				(int)(MINIMAP_CENTER + ray.dir_y * i), 0xFF0000);
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
	player_centered_minimap(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
}
