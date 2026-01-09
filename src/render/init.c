#include "cub3d.h"

static bool	init_mlx(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("mlx_init failed\n", game), false);
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (clean_up_mlx(game), print_error("mlx_new_window failed\n", game), false);
	game->image->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image->img)
		return (clean_up_mlx(game), print_error("mlx_new_image failed\n", game), false);
	game->image->addr = mlx_get_data_addr(game->image->img,
		&game->image->bits_per_pixel, &game->image->line_length,
		&game->image->endian);
	// Hooks
	mlx_hook(game->mlx_win, 17, 1L << 2, quit_game, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_hook, game);
	return (true);
}

bool	render(t_data *game)
{
	// TODO: init map width and height @ patrick
	while (game->map.arr[game->map_height])
		game->map_height++;
	game->tile_size = TILE_2D_BIG;
	if (game->map_height > MINIMAP_SIZE / TILE_2D_BIG)
		game->tile_size = TILE_2D_SMALL;
	//
	if (!init_mlx(game))
		return (false);
	render_game(game);
	mlx_loop(game->mlx);
	return (true);
}
