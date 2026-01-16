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
	if (col->x <= MINIMAP_SIZE && col->y < MINIMAP_SIZE)
	{
		col->tex_y += (MINIMAP_SIZE - col->y) * col->y_step_size;
		col->y = MINIMAP_SIZE + 1;
	}
	if (col->y_end > HEIGHT)
		col->y_end = HEIGHT;
	col->tex = &game->text[ray->side];
}

// static int	get_pixel_from_image(t_texture *tex, int x, int y)
// {
// 	if (y >= tex->height)
// 		return (*(int *)(tex->image.addr + tex->height - 1));
// 	return (*(int *)(tex->image.addr + y * tex->image.line_length
// 		+ x * (tex->image.bits_per_pixel / 8)));
// }

void	draw_texture_line(t_data *game, t_ray *ray, t_column *col)
{
	init_col(game, ray, col);
	int tex_bpp;
	int tex_line;
	char *tex_addr;
	int img_bpp;
	int img_line;
	char *img_addr;

	tex_bpp = col->tex->image.bits_per_pixel / 8;
	tex_line = col->tex->image.line_length;
	tex_addr = col->tex->image.addr;
	img_bpp = game->image->bits_per_pixel / 8;
	img_line = game->image->line_length;
	img_addr = game->image->addr;
	while (col->y < col->y_end && col->tex_y < col->tex->height)
	{
		// if (col->x > MINIMAP_SIZE || col->y > MINIMAP_SIZE)
		// ft_put_pixel(game->image, col->x, col->y,
		// 	get_pixel_from_image(col->tex, col->tex_x, (int)col->tex_y));
		*(int *)(img_addr + col->y * img_line + col->x * img_bpp) = *(int *)(tex_addr + (int)col->tex_y * tex_line + col->tex_x * tex_bpp);
		col->y++;
		col->tex_y += col->y_step_size;
	}
}
