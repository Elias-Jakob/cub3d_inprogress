#include "../../inc/cub3d.h"

static bool	init_mlx(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (mlx_destroy_display(game->mlx), free(game->mlx), false);
	// Hooks
	mlx_hook(game->mlx_win, 17, 1L << 2, quit_game, game);
	mlx_key_hook(game->mlx_win, key_hook, game);
	return (true);
}

bool	render_game(t_data *game)
{
	if (!init_mlx(game))
		return (false);
	mlx_loop(game->mlx);
	return (true);
}
