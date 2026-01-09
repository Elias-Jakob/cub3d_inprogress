#include "cub3d.h"

static void	init_minimap(t_data *game, t_minimap *map)
{
	map->n_tiles = MINIMAP_SIZE / game->tile_size;
	map->start_col = (int)game->player->x - map->n_tiles / 2;
	map->start_row = (int)game->player->y - map->n_tiles / 2;
	map->end_col = (int)game->player->x + map->n_tiles / 2 + 1;
	map->end_row = (int)game->player->y + map->n_tiles / 2 + 1;
	map->y = map->start_row;
	if (game->map_height < map->end_row)
		map->end_row = game->map_height;
	map->x_fract = game->player->x - (int)game->player->x;
	map->y_fract = game->player->y - (int)game->player->y;
}

static void	draw_minimap_square(t_data *game, double x, double y, int color)
{
	int	px;
	int	py;
	int	wall_end_x;
	int	wall_end_y;
	int	y_start;

	px = floor(x * game->tile_size);
	py = floor(y * game->tile_size);
	wall_end_x = px + game->tile_size - 1;
	wall_end_y = py + game->tile_size - 1;
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

static void	draw_minimap_player(t_data *game)
{
	int	y;
	int	x;

	// TODO: replace with a circle
	y = 0;
	while (y < 7)
	{
		x = 0;
		while (x < 7)
		{
			ft_put_pixel(game->image,
				MINIMAP_CENTER - 3 + x,
				MINIMAP_CENTER - 3 + y, MINIMAP_PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

void	player_centered_minimap(t_data *game)
{
	t_minimap	map;
	int	square_color;

	init_minimap(game, &map);
	while (map.y < map.end_row)
	{
		map.x = map.start_col;
		while (map.x < map.end_col)
		{
			if (map.y >= 0 && map.x >= 0 && map.y < game->map_height
				&& (size_t)map.x < ft_strlen(game->map.arr[map.y]))
			{
				square_color = MINIMAP_BG_COLOR;
				if (game->map.arr[map.y][map.x] == '1')
					square_color = MINIMAP_WALL_COLOR;
				draw_minimap_square(game, map.x - map.start_col - map.x_fract,
					map.y - map.start_row - map.y_fract, square_color);
			}
			map.x++;
		}
		map.y++;
	}
	draw_minimap_player(game);
}

void	draw_minimap_ray(t_data *game, t_ray *ray, int wall_dist)
{
	int	i;

	i = 0;
	while (i < wall_dist
		&& MINIMAP_CENTER + ray->dir_x * i < MINIMAP_SIZE
		&& MINIMAP_CENTER + ray->dir_y * i < MINIMAP_SIZE)
	{
		ft_put_pixel(game->image,
			(int)(MINIMAP_CENTER + ray->dir_x * i),
			(int)(MINIMAP_CENTER + ray->dir_y * i), MINIMAP_RAY_COLOR);
		i++;
	}
}
