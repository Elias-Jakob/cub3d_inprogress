#include "cub3d.h"

double	raycasting(t_data *game, int current_x_col)
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
	double side_dist_x; // the distance to the NEXT grid line position that is checked
	double side_dist_y;
	int	step_x; // Tells us in which direction we're moving through the map
	int	step_y;

	camera_x = 2 * current_x_col / (double)WIDTH - 1;
	// camera_x = 0; // straight ahead
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
			// printf("player_x = %f player_y = %f map_x = %d map_y = %d side_dist_x = %f side_dist_y = %f\n", game->player->x, game->player->y, map_x, map_y, side_dist_x, side_dist_y);
			hit = true;
		}
	}
	if (!side)
		return (side_dist_x - delta_dist_x);
	else
		return (side_dist_y - delta_dist_y);
}
