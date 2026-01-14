#include "cub3d.h"

void	clean_up_mlx(t_data *game)
{
	int	i_tex;

	if (game->image)
		mlx_destroy_image(game->mlx, game->image->img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	i_tex = 0;
	while (i_tex < N_TEXTURES && game->text[i_tex].image.img)
		mlx_destroy_image(game->mlx, game->text[i_tex++].image.img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	ft_put_pixel(t_img_data *image_data, int x, int y, int color)
{
	char	*pixel;
	// patrick: hab bounce check eingefuegt. ohne Bounds check mit negativen
	// bzw. zu großen x y Koordinaten in den Image-Buffer geschrieben
	// hat und dadurch außerhalb des allokierten Speichers 4 Bytes überschrieben wurden
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
    	return;

	pixel = image_data->addr + (y * image_data->line_length + x
		* (image_data->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
	// printf("x: %d y: %d pixel: %x\n", x, y, *pixel);
	// printf("MLX image\naddr: %p\nimg: %p\nbits_per_pixel: %d\nline_length: %d\nendian: %d\n",
	// 			image_data->addr, image_data->img, image_data->bits_per_pixel, image_data->line_length, image_data->endian);
}

unsigned long	get_timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
