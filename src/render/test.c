#include "../../inc/cub3d.h"

static int	close_button_hook(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (1);
}

int	create_base_window(void)
{
	t_game	game;

	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");

	mlx_hook(game.mlx_win, ON_DESTROY, 1L << 2, close_button_hook, &game);
	mlx_loop();
}
