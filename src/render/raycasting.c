/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejakob <ejakob@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:58:47 by ejakob            #+#    #+#             */
/*   Updated: 2026/02/09 11:58:52 by ejakob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	init_ray(t_player *player, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->delta_dist_x = INFINITY;
	ray->delta_dist_y = INFINITY;
	if (ray->dir_x != 0)
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y != 0)
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->step_x = -1;
	ray->step_y = -1;
	ray->wall_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	ray->wall_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	if (ray->dir_x > 0)
	{
		ray->step_x = 1;
		ray->wall_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
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
	if (ray->side == WEST && ray->step_x == -1)
		ray->side = EAST;
	if (ray->side == NORTH && ray->step_y == -1)
		ray->side = SOUTH;
	ray->wall_dist = ray->wall_dist_y - ray->delta_dist_y;
	if (ray->side == WEST || ray->side == EAST)
		ray->wall_dist = ray->wall_dist_x - ray->delta_dist_x;
}
