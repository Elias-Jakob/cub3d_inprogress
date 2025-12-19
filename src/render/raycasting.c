#include "cub3d.h"

// static void	cast_ray(t_data *game, int x)
// {
//
// }

static int	cast_2d_ray(t_data *game)
{
	bool	hit;
	int	map_x;
	int	map_y;

	hit = false;
	map_x = game->player->x;
	map_y = game->player->y;
	while (!hit)
	{
		map_x += (int)(game->player->dir_x);
		map_y -= (int)(game->player->dir_y);
		if (map_x >= game->map.x || map_y >= game->map.y)
			return (print_error("outside the map\n", game), 0);
		if (game->map.arr[map_y][map_x] == '1')
		{
			printf("map_x = %d map_y = %d\n", map_x, map_y);
			hit = true;
		}
	}
	return ((game->player->x - map_x + game->player->y - map_y) * TILE_2D - TILE_2D / 2);
}

int	raycasting(t_data *game)
{
	return (cast_2d_ray(game));
}
