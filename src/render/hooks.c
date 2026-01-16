#include "cub3d.h"

static void rotate_player(t_player *player, double rot_angle)
{
	double old_dir_x;
	double old_dir_y;

	old_dir_x = player->dir_x;
	old_dir_y = player->dir_y;
	if (old_dir_x == 0 && old_dir_y == -1)
		player->start_time = get_timestamp();
	player->dir_x = old_dir_x * cos(rot_angle) - old_dir_y * sin(rot_angle);
	player->dir_y = old_dir_x * sin(rot_angle) + old_dir_y * cos(rot_angle);
	// TODO:
	printf("dirx = %f diry = %f\n", player->dir_x, player->dir_y);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	player->full_rotation += rot_angle;
	if (player->full_rotation >= PI * 2)
	{
		printf("time to rotate 360: %lums\n", get_timestamp() - player->start_time);
		player->full_rotation = 0;
	}
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
