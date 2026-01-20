#include "cub3d.h"

static bool	wall_collision(char **map, double x, double y)
{
	return (map[(int)y][(int)x] == '1');
}

static bool	near_door(t_data *game)
{
	int	map_x;
	int	map_y;
	int	row;
	int	col;

	map_x = (int)game->player->x;
	map_y = (int)game->player->y;
	row = -3;
	while (row <= 3)
	{
		col = -3;
		while (col <= 3)
		{
			if (game->map.arr[map_y + row][map_x + col] == 'D')
			{
				if (game->door.start_opening == 0)
					game->door.start_opening = get_timestamp();
				return (true);
			}
			col++;
		}
		row++;
	}
	return (game->door.start_opening = 0, false);
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
	game->door.opening = near_door(game);
}

void rotate_player(t_player *player, double rot_angle)
{
	double old_dir_x;
	double old_dir_y;

	old_dir_x = player->dir_x;
	old_dir_y = player->dir_y;
	player->dir_x = old_dir_x * cos(rot_angle) - old_dir_y * sin(rot_angle);
	player->dir_y = old_dir_x * sin(rot_angle) + old_dir_y * cos(rot_angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
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
