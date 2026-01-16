#include "cub3d.h"

static void	init_col(t_data *game, t_ray *ray, t_column *col)
{
	col->wall_x = game->player->x + ray->wall_dist * ray->dir_x;
	if (ray->side == WEST || ray->side == EAST)
		col->wall_x = game->player->y + ray->wall_dist * ray->dir_y;
	col->wall_x -= (int)col->wall_x;
	col->tex = &game->text[ray->side];
	col->tex_x = col->tex->width * col->wall_x;
	col->y_start = HEIGHT / 2 - HEIGHT / ray->wall_dist;
	col->y_end = HEIGHT / 2 + HEIGHT / ray->wall_dist;
	if (col->y_end > HEIGHT)
		col->y_end = HEIGHT;
	col->line_height = (HEIGHT / ray->wall_dist) * 2;
	col->y_step_size = (double)col->tex->height / col->line_height;
	col->tex_y = 0;
	col->y = col->y_start;
	if (col->y < 0)
	{
		col->tex_y = -col->y * col->y_step_size;
		col->y = 0;
	}
	if (col->x <= MINIMAP_SIZE && col->y < MINIMAP_SIZE)
	{
		col->tex_y += (MINIMAP_SIZE - col->y) * col->y_step_size;
		col->y = MINIMAP_SIZE + 1;
	}
}

void	draw_texture_line(t_data *game, t_ray *ray, t_column *col)
{
	int		tex_line;
	int		img_line;
	char	*tex_addr;
	char	*img_addr;

	init_col(game, ray, col);
	tex_line = col->tex->image.line_length;
	img_line = game->image->line_length;
	tex_addr = col->tex->image.addr + col->tex_x
		* (col->tex->image.bits_per_pixel / 8);
	img_addr = game->image->addr + col->x * (game->image->bits_per_pixel / 8);
	while (col->y < col->y_end && col->tex_y < col->tex->height)
	{
		*(int *)(img_addr + col->y * img_line) = *(int *)(tex_addr
				+ (int)col->tex_y * tex_line);
		col->y++;
		col->tex_y += col->y_step_size;
	}
}
