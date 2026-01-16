#include "cub3d.h"

static void	init_ray(t_player *player, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	// for dirx = 0.149438 diry = -0.988771
	// delta_dist_x = 6.71
	// delta_dist_y = 1.01
	// EXAMPLE
	// 0.71, -0.69
	ray->delta_dist_x = INFINITY;
	ray->delta_dist_y = INFINITY;
	if (ray->dir_x != 0)
		ray->delta_dist_x = fabs(1 / ray->dir_x); // 1.4
	if (ray->dir_y != 0)
		ray->delta_dist_y = fabs(1 / ray->dir_y); // 1.44
	ray->map_x = (int)player->x; // 3.8
	ray->map_y = (int)player->y; // 5.7
	ray->step_x = -1;
	ray->step_y = -1;
	ray->wall_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	ray->wall_dist_y = (player->y - ray->map_y) * ray->delta_dist_y; // 0.7 * 1.44 = 1
	if (ray->dir_x > 0)
	{
		ray->step_x = 1;
		ray->wall_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x; // 0.2 * 1.4 = 0.28
	}
	if (ray->dir_y > 0)
	{
		ray->step_y = 1;
		ray->wall_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void	raycasting(t_data *game, t_ray *ray, int x)
{
	init_ray(game->player, ray, x);
	// DDA loop
	while (game->map.arr[ray->map_y][ray->map_x] != '1')
	{
		if (ray->wall_dist_x < ray->wall_dist_y)
		{
			ray->wall_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = WEST;
		}
		else
		{
			ray->wall_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = NORTH;
		}
	}
	if (ray->side == WEST && ray->step_x == 1)
		ray->side = EAST;
	if (ray->side == NORTH && ray->step_y == 1)
		ray->side = SOUTH;
	ray->wall_dist = ray->wall_dist_y - ray->delta_dist_y;
	if (ray->side == WEST || ray->side == EAST)
		ray->wall_dist = ray->wall_dist_x - ray->delta_dist_x;
}
