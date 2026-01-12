#include "cub3d.h"

static void rotate_player(t_player *player, double rot_angle)
{
	double old_dir_x;
	double old_dir_y;

	old_dir_x = player->dir_x;
	old_dir_y = player->dir_y;
	player->dir_x = old_dir_x * cos(rot_angle) - old_dir_y * sin(rot_angle);
	player->dir_y = old_dir_x * sin(rot_angle) + old_dir_y * cos(rot_angle);
	// printf("old_dir_x: %f * cos(rot_angle): %f - old_dir_y: %f * sin(rot_angle): %f\n", old_dir_x, cos(rot_angle), old_dir_y, sin(rot_angle));
	// printf("dir_x = %f dir_y = %f\n", player->dir_x, player->dir_y);
}

int	quit_game(t_data *game)
{
	clean_up_mlx(game);
	cleanup_parser(game, SUCCESS);
	exit(0);
}

int	key_hook(int key_code, t_data *game)
{
	if (key_code == XK_Escape)
		quit_game(game);
	else if (key_code == XK_Left)
		rotate_player(game->player, 0.1);
	else if (key_code == XK_Right)
		rotate_player(game->player, -0.1);
	else if (key_code == XK_w)
		game->player->y -= 5;
	else if (key_code == XK_a)
		game->player->x -= 5;
	else if (key_code == XK_s)
		game->player->y += 5;
	else if (key_code == XK_d)
		game->player->x += 5;
	render_game(game);
	return (0);
}
