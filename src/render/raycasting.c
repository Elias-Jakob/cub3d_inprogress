#include "cub3d.h"

static void	init_ray(t_player *player, t_ray *ray)
{
	ray->camera_x = 2 * ray->col / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	// for dirx = 0.149438 diry = -0.988771
	// delta_dist_x = 6.71
	// delta_dist_y = 1.01
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = false;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->step_x = -1;
	ray->step_y = -1;
	ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	if (ray->dir_x > 0)
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y > 0)
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

double	raycasting(t_data *game, t_ray *ray)
{
	init_ray(game->player, ray);
	// DDA loop
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = WEST;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = NORTH;
		}
		if (game->map.arr[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
	}
	if (ray->side == WEST && ray->step_x == 1)
		ray->side = EAST;
	if (ray->side == NORTH && ray->step_y == 1)
		ray->side = SOUTH;

	if (ray->side == WEST || ray->side == EAST)
		return (ray->side_dist_x - ray->delta_dist_x);
	else
		return (ray->side_dist_y - ray->delta_dist_y);
}
