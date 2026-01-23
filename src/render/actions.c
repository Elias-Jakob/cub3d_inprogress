#include "cub3d.h"

static bool	wall_collision(char **map, double x, double y)
{
	return (map[(int)y][(int)x] == '1');
}

void	set_new_player_pos(t_data *game, double x, double y)
{
	char	**map;
	t_player	*p;

	map = game->map.arr;
	p = game->player;
	if (!wall_collision(map, x + COLLISION_MARGIN, p->y)
		&& !wall_collision(map, x - COLLISION_MARGIN, p->y)
		&& !wall_collision(map, x, p->y + COLLISION_MARGIN)
		&& !wall_collision(map, x, p->y - COLLISION_MARGIN))
		p->x = x;
	if (!wall_collision(map, p->x + COLLISION_MARGIN, y)
		&& !wall_collision(map, p->x - COLLISION_MARGIN, y)
		&& !wall_collision(map, p->x, y + COLLISION_MARGIN)
		&& !wall_collision(map, p->x, y - COLLISION_MARGIN))
		p->y = y;
}

void rotate_player(t_player *player, double rot_angle)
{
	player->angle += rot_angle;
	if (player->angle > PI * 2)
		player->angle -= PI * 2;
	angle_to_vector(player);
	// TIME ROTATION
	/*
	if (old_dir_x == 0 && old_dir_y == -1)
		player->start_time = get_timestamp();
	player->full_rotation += rot_angle;
	if (player->full_rotation >= PI * 2)
	{
		printf("time to rotate 360: %lums\n", get_timestamp() - player->start_time);
		player->full_rotation = 0;
	}
	*/
	// TODO:
	// printf("dirx = %f diry = %f\n", player->dir_x, player->dir_y);
}

int	quit_game(t_data *game)
{
	clean_up_mlx(game);
	cleanup_parser(game, SUCCESS);
	exit(0);
}
