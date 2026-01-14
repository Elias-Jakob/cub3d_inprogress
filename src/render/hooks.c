#include "cub3d.h"

static void rotate_player(t_player *player, double rot_angle)
{
	double old_dir_x;
	double old_dir_y;

	old_dir_x = player->dir_x;
	old_dir_y = player->dir_y;
	player->dir_x = old_dir_x * cos(rot_angle) - old_dir_y * sin(rot_angle);
	player->dir_y = old_dir_x * sin(rot_angle) + old_dir_y * cos(rot_angle);
	// TODO:
	// printf("dirx = %f diry = %f\n", player->dir_x, player->dir_y);
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
	char	**map;
	t_player	*p;

	map = game->map.arr;
	p = game->player;
	if (map[(int)p->y][(int)(x + COLLISION_MARGIN)] != '1'
		&& map[(int)p->y][(int)(x - COLLISION_MARGIN)] != '1'
		&& map[(int)(p->y + COLLISION_MARGIN)][(int)x] != '1'
		&& map[(int)(p->y - COLLISION_MARGIN)][(int)x] != '1')
		game->player->x = x;
	if (map[(int)y][(int)(p->x + COLLISION_MARGIN)] != '1'
		&& map[(int)y][(int)(p->x - COLLISION_MARGIN)] != '1'
		&& map[(int)(y + COLLISION_MARGIN)][(int)p->x] != '1'
		&& map[(int)(y - COLLISION_MARGIN)][(int)p->x] != '1')
		game->player->y = y;
}

// static void	handle_player_movement(t_data *game, int key_code)
// {
// 	t_player	*p;
// 	double	step_x;
// 	double	step_y;
//
// 	p = game->player;
// 	step_x = p->dir_x * 0.1;
// 	step_y = p->dir_y * 0.1;
// 	if (key_code == XK_w)
// 		set_new_player_pos(game, p->x + step_x, p->y + step_y);
// 	else if (key_code == XK_a)
// 		set_new_player_pos(game, p->x + step_y, p->y - step_x);
// 	else if (key_code == XK_s)
// 		set_new_player_pos(game, p->x - step_x, p->y - step_y);
// 	else if (key_code == XK_d)
// 		set_new_player_pos(game, p->x - step_y, p->y + step_x);
// }

int	render_loop_hook(t_data *game)
{
	if (game->action == ROTATE_LEFT)
		rotate_player(game->player, -ROTATION_ANGLE);
	else if (game->action == ROTATE_RIGHT)
		rotate_player(game->player, ROTATION_ANGLE);
	else if (game->action == MOVE_FORWARD)
		set_new_player_pos(game,
			game->player->x + game->player->dir_x * STEP_SIZE,
			game->player->y + game->player->dir_y * STEP_SIZE);
	else if (game->action == MOVE_LEFT)
		set_new_player_pos(game,
			game->player->x - game->player->dir_y * STEP_SIZE,
			game->player->y + game->player->dir_x * STEP_SIZE);
	else if (game->action == MOVE_BACKWARD)
		set_new_player_pos(game,
			game->player->x - game->player->dir_x * STEP_SIZE,
			game->player->y - game->player->dir_y * STEP_SIZE);
	else if (game->action == MOVE_RIGHT)
		set_new_player_pos(game,
			game->player->x + game->player->dir_y * STEP_SIZE,
			game->player->y - game->player->dir_x * STEP_SIZE);
	else
		return (0);
	// if (get_timestamp() - game->last_time_rendered > 15)
	render_game(game);
	return (0);
}

int	key_press_hook(int key_code, t_data *game)
{
	game->action = key_code;
	if (key_code == XK_Escape)
		quit_game(game);
	return (0);
}

int	key_release_hook(int key_code, t_data *game)
{
	(void)key_code;
	game->action = NONE;
	return (0);
}
