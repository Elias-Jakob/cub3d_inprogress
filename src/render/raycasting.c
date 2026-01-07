#include "cub3d.h"

double	raycasting(t_data *game, t_ray *ray)
{
	ray->camera_x = 2 * ray->col / (double)WIDTH - 1;
	// camera_x = 0; // straight ahead
	ray->dir_x = game->player->dir_x + game->player->plane_x * ray->camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y * ray->camera_x;
	// for dirx = 0.149438 diry = -0.988771
	// delta_dist_x = 6.71
	// delta_dist_y = 1.01
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	// INFO: ray vectors evaluate to respective direction vector if camera_x == 0
	ray->hit = false;
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
	ray->step_x = -1;
	ray->step_y = -1;
	ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	if (ray->dir_x > 0)
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y > 0)
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_dist_y;
	}
	// DDA loop
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = false;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = true;
		}
		if (game->map.arr[ray->map_y][ray->map_x] == '1')
		{
			// printf("player_x = %f player_y = %f map_x = %d map_y = %d side_dist_x = %f side_dist_y = %f\n", game->player->x, game->player->y, map_x, map_y, side_dist_x, side_dist_y);
			ray->hit = true;
		}
	}
	if (!ray->side)
		return (ray->side_dist_x - ray->delta_dist_x);
	else
		return (ray->side_dist_y - ray->delta_dist_y);
}
