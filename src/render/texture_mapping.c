#include "cub3d.h"

static void	init_col(t_data *game, t_ray *ray, t_column *col)
{
	if (ray->side == WEST || ray->side == EAST)
		col->wall_x = game->player->y + ray->wall_dist * ray->dir_y;
	else
		col->wall_x = game->player->x + ray->wall_dist * ray->dir_x;
	col->wall_x -= (int)col->wall_x;
	col->tex_x = game->text[ray->side].width * col->wall_x;
	col->y_start = HEIGHT / 2 - HEIGHT / ray->wall_dist;
	col->y_end = HEIGHT / 2 + HEIGHT / ray->wall_dist;
	col->line_height = (HEIGHT / ray->wall_dist) * 2;
	col->y_step_size = (double)game->text[ray->side].height / col->line_height;
	col->tex_y = 0;
	col->y = col->y_start;
	if (col->y < 0)
	{
		col->tex_y = -col->y * col->y_step_size;
		col->y = 0;
	}
	col->tex = &game->text[ray->side].image;
}

static int	get_pixel_from_image(t_img_data *img, int x, int y)
{
	int	pos_1d;

	pos_1d = y * img->line_length
		+ x * (img->bits_per_pixel / 8);
	return (*(int *)(img->addr + pos_1d));
}

void	draw_texture_line(t_data *game, t_ray *ray, t_column *col)
{
	init_col(game, ray, col);
	while (col->y < col->y_end && col->y < HEIGHT)
	{
		if (col->x > MINIMAP_SIZE || col->y > MINIMAP_SIZE)
			ft_put_pixel(game->image, col->x, col->y,
				get_pixel_from_image(col->tex, col->tex_x, (int)col->tex_y));
		col->y++;
		if ((int)(col->tex_y + col->y_step_size) < game->text[ray->side].height)
			col->tex_y += col->y_step_size;
	}
}
