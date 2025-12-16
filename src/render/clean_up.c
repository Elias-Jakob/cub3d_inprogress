#include "../../inc/cub3d.h"

void	clean_up_mlx(t_data *game)
{
	// clear image as well
	// mlx_destroy_image(view_data->mlx, view_data->img->image);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
