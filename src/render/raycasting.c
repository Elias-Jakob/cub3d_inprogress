#include "cub3d.h"

// static void	cast_ray(t_data *game, int x)
// {
//
// }

static double	cast_2d_ray(t_data *game)
{
	bool	hit;
	int	map_x;
	int	map_y;
	double	camera_x; // current x column normalized to direction vector
	double	ray_dir_x; // ray direction vector
	double	ray_dir_y;
	double	delta_dist_x; // ray length to travel one grid unit
	double	delta_dist_y;
	bool	side; // was a NS or a EW wall hit?
	double side_dist_x; // Tells us how far the current ray position and the next grid lines are apart from each other
	double side_dist_y;
	int	step_x; // Tells us in which direction we're moving through the map
	int	step_y;

	// (only one ray for understanding of the concept)
	// camera_x = 2 * current_x_col / (double)WIDTH - 1;
	camera_x = 0; // straight ahead
	ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray_dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	// INFO: ray vectors evaluate to respective direction vector if camera_x == 0
	hit = false;
	map_x = (int)game->player->x;
	map_y = (int)game->player->y;
	step_x = -1;
	step_y = -1;
	side_dist_x = (game->player->x - map_x) * delta_dist_x;
	side_dist_y = (game->player->y - map_y) * delta_dist_y;
	if (ray_dir_x > 0)
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player->x) * delta_dist_x;
	}
	if (ray_dir_y > 0)
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player->y) * delta_dist_y;
	}
	// DDA loop
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = false;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = true;
		}
		if (game->map.arr[map_y][map_x] == '1')
		{
			printf("player_x = %f player_y = %f map_x = %d map_y = %d side_dist_x = %f side_dist_y = %f\n", game->player->x, game->player->y, map_x, map_y, side_dist_x, side_dist_y);
			hit = true;
		}
	}
	if (!side)
		return ((map_x - game->player->x + (1 - step_x) / 2) / ray_dir_x);
	else
		return ((map_y - game->player->y + (1 - step_y) / 2) / ray_dir_y);
}

int	raycasting(t_data *game)
{
	double ray = cast_2d_ray(game);
	printf("ray = %f\n", ray);
	return ((int)(ray * TILE_2D));
}
