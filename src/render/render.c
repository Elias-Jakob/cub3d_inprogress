#include "cub3d.h"

static void	fill_backgrounds(t_data *game)
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
				ft_put_pixel(game->image, x, y, create_trgb(0, game->rgb.ceil[RED], game->rgb.ceil[GREEN], game->rgb.ceil[BLUE]));
			else
				ft_put_pixel(game->image, x, y, create_trgb(0, game->rgb.floor[RED], game->rgb.floor[GREEN], game->rgb.floor[BLUE]));
			x++;
		}
		y++;
	}
}

static void	draw_rays(t_data *game)
{
	double	wall_dist;
	t_ray	ray;
	t_column	col;
	t_img_data	text_img;
	// int	color;

	col.x = 0;
	while (col.x < WIDTH)
	{
		ray.col = col.x;
		wall_dist = raycasting(game, &ray);
		draw_minimap_ray(game, &ray, (int)(wall_dist * game->tile_size));
		if (ray.side == WEST || ray.side == EAST)
			col.wall_x = game->player->y + wall_dist * ray.dir_y;
		else
			col.wall_x = game->player->x + wall_dist * ray.dir_x;
		col.wall_x -= (int)col.wall_x;
		col.tex_x = game->text[ray.side].width * col.wall_x;
		if (wall_dist < 1)
			wall_dist = 1;
		col.y_start = HEIGHT / 2 - HEIGHT / wall_dist;
		col.y_end = HEIGHT / 2 + HEIGHT / wall_dist;
		col.line_height = (HEIGHT / wall_dist) * 2;
		col.y_step_size = (double)game->text[ray.side].height / col.line_height;
		col.tex_y = col.y_step_size;
		col.y = col.y_start;
		while (col.y < col.y_end)
		{
			col.tex_y += col.y_step_size;
			text_img = game->text[ray.side].image;
			printf("tex_x: %d tex_y: %f\n", col.tex_x, col.tex_y);
			printf("%c\n", (unsigned int)text_img.addr[63]);
			ft_put_pixel(game->image, col.x, col.y,
				text_img.addr[(int)col.tex_y * text_img.line_length + col.tex_x * (text_img.bits_per_pixel / 8)]);
			col.y++;
			return ;
		}
			return ;
		// draw_minimap_ray(game, &ray, (int)(wall_dist * game->tile_size));
		// if (wall_dist < 1)
		// 	wall_dist = 1;
		// for (; col.y < HEIGHT / wall_dist; col.y++)
		// {
		// 	color = 0xFF0000;
		// 	if (ray.side == SOUTH)
		// 		color = 0x00FF00;
		// 	else if (ray.side == WEST)
		// 		color = 0x0000FF;
		// 	else if (ray.side == EAST)
		// 		color = 0x000000;
		// 	if (col.x > MINIMAP_SIZE || HEIGHT / 2 - col.y > MINIMAP_SIZE) // dont overwrite the minimap
		// 		ft_put_pixel(game->image, col.x, HEIGHT / 2 - col.y, color);
		// 	ft_put_pixel(game->image, col.x, HEIGHT / 2 + col.y, color);
		// }
		col.x++;
	}
}

int	render_game(t_data *game)
{
	game->last_time_rendered = get_timestamp();
	fill_backgrounds(game);
	player_centered_minimap(game);
	draw_rays(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
	return (0);
}
