#include "../../inc/cub3d.h"

void	ft_put_pixel(t_img_data *image_data, int x, int y, int color)
{
	char	*pixel;

	pixel = image_data->addr + (y * image_data->line_length + x
		* (image_data->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
	// printf("x: %d y: %d pixel: %x\n", x, y, *pixel);
	// printf("MLX image\naddr: %p\nimg: %p\nbits_per_pixel: %d\nline_length: %d\nendian: %d\n", 
	// 			image_data->addr, image_data->img, image_data->bits_per_pixel, image_data->line_length, image_data->endian);
}
