#include "../../inc/cub3d.h"

void	clean_up_mlx(t_data *game)
{
	if (game->image)
		mlx_destroy_image(game->mlx, game->image->img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
