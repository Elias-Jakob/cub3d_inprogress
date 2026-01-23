#include "cub3d.h"

static void	draw_minimap_player(t_data *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->player_size)
	{
		x = 0;
		while (x < game->player_size)
		{
			ft_put_pixel(game->image,
				MINIMAP_CENTER - game->player_center + x,
				MINIMAP_CENTER - game->player_center + y, MINIMAP_PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

static void	init_minimap(t_data *game, t_minimap *map)
{
	map->start_col = (int)game->player->x - N_TILES / 2;
	map->start_row = (int)game->player->y - N_TILES / 2;
	map->end_col = (int)game->player->x + N_TILES / 2 + 1;
	map->end_row = (int)game->player->y + N_TILES / 2 + 1;
	map->y = map->start_row;
	if (game->map_height < map->end_row)
		map->end_row = game->map_height;
	map->x_fract = game->player->x - (int)game->player->x - 0.1;
	map->y_fract = game->player->y - (int)game->player->y - 0.1;
}

static void	draw_minimap_square(t_data *game, double x, double y, int color)
{
	int	px;
	int	py;
	int	wall_end_x;
	int	wall_end_y;
	int	y_start;

	px = floor(x * TILE_SIZE_2D);
	py = floor(y * TILE_SIZE_2D);
	wall_end_x = px + TILE_SIZE_2D - 1;
	wall_end_y = py + TILE_SIZE_2D - 1;
	y_start = py;
	if (wall_end_x <= MINIMAP_SIZE && wall_end_y <= MINIMAP_SIZE)
		ft_put_pixel(game->image, wall_end_x, wall_end_y, MINIMAP_GRID_COLOR);
	while (px < wall_end_x && px < MINIMAP_SIZE)
	{
		while (py < wall_end_y && py < MINIMAP_SIZE)
		{
			if (wall_end_y <= MINIMAP_SIZE)
				ft_put_pixel(game->image, px, wall_end_y, MINIMAP_GRID_COLOR);
			if (wall_end_x <= MINIMAP_SIZE)
				ft_put_pixel(game->image, wall_end_x, py, MINIMAP_GRID_COLOR);
			ft_put_pixel(game->image, px, py, color);
			py++;
		}
		py = y_start;
		px++;
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

void	draw_minimap_ray(t_data *game, t_ray *ray, int x1, int y1)
{
	int	x0;
	int	y0;

	x0 = MINIMAP_CENTER;
	y0 = MINIMAP_CENTER;
	x1 += x0;
	y1 += y0;
	ray->wall_dist_x = ray->delta_dist_x;
	ray->wall_dist_y = ray->delta_dist_y;
	while (x0 != x1 && y0 != y1 && x0 < MINIMAP_SIZE && y0 < MINIMAP_SIZE)
	{
		ft_put_pixel(game->image, x0, y0, MINIMAP_RAY_COLOR);
		if (ray->wall_dist_x < ray->wall_dist_y)
		{
			ray->wall_dist_x += ray->delta_dist_x;
			x0 += ray->step_x;
		}
		else
		{
			ray->wall_dist_y += ray->delta_dist_y;
			y0 += ray->step_y;
		}
	}
}
