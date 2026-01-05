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
	// plane
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}

int	quit_game(t_data *game)
{
	clean_up_mlx(game);
	cleanup_parser(game, SUCCESS);
	exit(0);
}

void	set_new_player_pos(t_data *game, double x, double y)
{
	if (game->map.arr[(int)y][(int)x] == '1')
		return ;
	game->player->x = x;
	game->player->y = y;
}

static void	handle_player_movement(t_data *game, int key_code)
{
	t_player	*p;
	double	step_x;
	double	step_y;

	p = game->player;
	step_x = p->dir_x * 0.1;
	step_y = p->dir_y * 0.1;
	if (key_code == XK_w)
		set_new_player_pos(game, p->x + step_x, p->y + step_y);
	else if (key_code == XK_a)
		set_new_player_pos(game, p->x + step_y, p->y - step_x);
	else if (key_code == XK_s)
		set_new_player_pos(game, p->x - step_x, p->y - step_y);
	else if (key_code == XK_d)
		set_new_player_pos(game, p->x - step_y, p->y + step_x);
}

int	key_hook(int key_code, t_data *game)
{
	if (key_code == XK_Escape)
		quit_game(game);
	else if (key_code == XK_Left)
		rotate_player(game->player, -0.05);
	else if (key_code == XK_Right)
		rotate_player(game->player, 0.05);
	else
		handle_player_movement(game, key_code);
	render_game(game);
	return (0);
}
