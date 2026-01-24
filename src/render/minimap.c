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
	map->start_col = (int)game->player->x - N_TILES;
	map->start_row = (int)game->player->y - N_TILES;
	map->end_col = (int)game->player->x + N_TILES + 1;
	map->end_row = (int)game->player->y + N_TILES + 1;
	map->x = map->start_col - 1;
	map->y = map->start_row;
	if (game->map_height < map->end_row)
		map->end_row = game->map_height;
	map->x_offset = game->player->x - (int)game->player->x - 0.1;
	map->y_offset = game->player->y - (int)game->player->y - 0.1;
}

static void	draw_minimap_tile(t_data *game, t_minimap *map)
{
	map->x1 = map->x0 + TILE_SIZE_2D - 1;
	map->y1 = map->y0 + TILE_SIZE_2D - 1;
	while (map->y0 < map->y1 && map->y0 <= MINIMAP_SIZE)
	{
		draw_tile_line(game, map, map->x0);
		map->y0++;
	}
	if (map->y0 < MINIMAP_SIZE)
	{
		map->tile_color = MINIMAP_GRID_COLOR;
		draw_tile_line(game, map, map->x0);
	}
}

void	draw_minimap(t_data *game)
{
	t_minimap	map;
	
	init_minimap(game, &map);
	while (map.y < map.end_row)
	{
		while (++map.x < map.end_col)
		{
			if (map.y < 0 || map.x < 0 || map.y >= game->map_height
				|| (size_t)map.x >= ft_strlen(game->map.arr[map.y]))
				continue ;
			map.tile_color = MINIMAP_BG_COLOR;
			if (game->map.arr[map.y][map.x] == '1')
				map.tile_color = MINIMAP_WALL_COLOR;
			map.x0 = (int)floor((map.x - map.start_col - map.x_offset) * TILE_SIZE_2D);
			map.y0 = (int)floor((map.y - map.start_row - map.y_offset) * TILE_SIZE_2D);
			draw_minimap_tile(game, &map);
		}
		map.y++;
		map.x = map.start_col - 1;
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
