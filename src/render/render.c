/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejakob <ejakob@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:16:44 by ejakob            #+#    #+#             */
/*   Updated: 2026/02/09 12:17:13 by ejakob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	fill_background(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x <= MINIMAP_SIZE && y <= MINIMAP_SIZE)
				ft_put_pixel(game->image, x, y, MINIMAP_BG_COLOR);
			else if (y < HEIGHT / 2)
				ft_put_pixel(game->image, x, y, game->rgb.ceil);
			else
				ft_put_pixel(game->image, x, y, game->rgb.floor);
			x++;
		}
		y++;
	}
}

int	render_game(t_data *game)
{
	t_ray		ray;
	t_column	col;

	game->last_time_rendered = get_timestamp();
	fill_background(game);
	draw_minimap(game);
	col.x = 0;
	while (col.x < WIDTH)
	{
		raycasting(game, &ray, col.x);
		draw_minimap_ray(game, &ray,
			(int)round(ray.dir_x * ray.wall_dist * TILE_SIZE_2D),
			(int)round(ray.dir_y * ray.wall_dist * TILE_SIZE_2D));
		draw_texture_line(game, &ray, &col);
		col.x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
	return (0);
}
