#include "cub3d.h"

int	render_loop_hook(t_data *game)
{
	if (game->turn_action == ROTATE_LEFT)
		rotate_player(game->player, -ROTATION_ANGLE);
	else if (game->turn_action == ROTATE_RIGHT)
		rotate_player(game->player, ROTATION_ANGLE);
	if (game->move_action == MOVE_FORWARD)
		set_new_player_pos(game,
			game->player->x + game->player->dir_x * STEP_SIZE,
			game->player->y + game->player->dir_y * STEP_SIZE);
	else if (game->move_action == MOVE_LEFT)
		set_new_player_pos(game,
			game->player->x - game->player->dir_y * STEP_SIZE,
			game->player->y + game->player->dir_x * STEP_SIZE);
	else if (game->move_action == MOVE_BACKWARD)
		set_new_player_pos(game,
			game->player->x - game->player->dir_x * STEP_SIZE,
			game->player->y - game->player->dir_y * STEP_SIZE);
	else if (game->move_action == MOVE_RIGHT)
		set_new_player_pos(game,
			game->player->x + game->player->dir_y * STEP_SIZE,
			game->player->y - game->player->dir_x * STEP_SIZE);
	if (get_timestamp() - game->last_time_rendered >= 10)
		render_game(game);
	return (0);
}

int	key_press_hook(int key_code, t_data *game)
{
	if (key_code == XK_Left || key_code == XK_Right)
		game->turn_action = key_code;
	else if (key_code == XK_Escape)
		quit_game(game);
	else
		game->move_action = key_code;
	return (0);
}

int	key_release_hook(int key_code, t_data *game)
{
	if (key_code == XK_Left || key_code == XK_Right)
		game->turn_action = NONE;
	else
		game->move_action = NONE;
	return (0);
}
