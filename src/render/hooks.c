#include "../../inc/cub3d.h"

int	quit_game(t_data *game)
{
	clean_up_mlx(game);
	free(game->player);
	free(game->image);
	cleanup_parser(game, SUCCESS);
	exit(0);
}

int	key_hook(int key_code, t_data *game)
{
	if (key_code == XK_Escape)
		quit_game(game);
	else if (key_code == XK_Left)
		;
	else if (key_code == XK_Right)
		;
	else if (key_code == XK_w)
		game->player->y -= 5;
	else if (key_code == XK_a)
		game->player->x -= 5;
	else if (key_code == XK_s)
		game->player->y += 5;
	else if (key_code == XK_d)
		game->player->x += 5;
	draw_image(game);
	return (0);
}
