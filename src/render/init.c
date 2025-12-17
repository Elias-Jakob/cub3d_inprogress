#include "../../inc/cub3d.h"

static bool	init_mlx(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (clean_up_mlx(game), false);
	game->image->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image->img)
		return (clean_up_mlx(game), false);
	game->image->addr = mlx_get_data_addr(game->image->img,
		&game->image->bits_per_pixel, &game->image->line_length,
		&game->image->endian);
	// Hooks
	mlx_hook(game->mlx_win, 17, 1L << 2, quit_game, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_hook, game);
	// mlx_key_hook(game->mlx_win, key_hook, game);
	return (true);
}

void	fill_background(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(game->image, x, y, 0x8a8686);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *game)
{
	int	y;
	int	x;
	
	y = 0;
	while (y < 6)
	{
		x = 0;
		while (x < 6)
		{
			ft_put_pixel(game->image, game->player->x+x+1, game->player->y+y, 0xFFFF00);
			x++;
		}
		y++;
	}
	// direction
}

void	draw_image(t_data *game)
{
	fill_background(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image->img, 0, 0);
}

bool	render_game(t_data *game)
{
	if (!init_mlx(game))
		return (false);
	game->player->x = 300;
	game->player->y = 300;
	draw_image(game);
	mlx_loop(game->mlx);
	return (true);
}
