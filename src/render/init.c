#include "cub3d.h"

static bool	load_textures(t_data *game)
{
	int	i_tex;
	t_texture	*texture;

	i_tex = 0;
	while (i_tex < N_TEXTURES)
	{
		texture = &game->text[i_tex++];
		if (!texture->is_png)
			texture->image.img = mlx_xpm_file_to_image(game->mlx, texture->path, &texture->width, &texture->height);
		// TODO: mlx_png_file_to_image does not work... Check if its OK to only allow the use of .xpm files?
		// else
		// 	texture.src = mlx_png_file_to_image(game->mlx, texture.path, &texture.width, &texture.height);
		if (!texture->image.img)
			return (print_error("failed to load texture: ", game, 0),
				printf("%s\n", texture->path), false);
		texture->image.addr = mlx_get_data_addr(texture->image.img,
			&texture->image.bits_per_pixel, &texture->image.line_length, &texture->image.endian);
		printf("w = %d h = %d\n", texture->width, texture->height);
		// TODO: (possible) should we error out if a texture is not quadratic?
	}
	return (true);
}

static bool	init_mlx(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("mlx_init failed\n", game, 0), false);
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (clean_up_mlx(game), print_error("mlx_new_window failed\n", game, 0), false);
	game->image->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image->img)
		return (clean_up_mlx(game), print_error("mlx_new_image failed\n", game, 0), false);
	game->image->addr = mlx_get_data_addr(game->image->img,
		&game->image->bits_per_pixel, &game->image->line_length,
		&game->image->endian);
	if (!load_textures(game))
		return (clean_up_mlx(game), false);
	// Hooks
	mlx_hook(game->mlx_win, 17, 1L << 2, quit_game, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_hook, game);
	// TODO: add on key release key hook
	// mlx_hook(game->mlx_win, 3, 1L << 0, key_hook, game);
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
	// mlx_loop_hook(game->mlx, render_game, game);
	mlx_loop(game->mlx);
	return (true);
}
