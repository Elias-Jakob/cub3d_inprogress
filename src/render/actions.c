/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejakob <ejakob@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:33:37 by ejakob            #+#    #+#             */
/*   Updated: 2026/02/09 11:34:22 by ejakob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static bool	wall_collision(char **map, double x, double y)
{
	return (map[(int)y][(int)x] == '1');
}

void	set_new_player_pos(t_data *game, double x, double y)
{
	char		**map;
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

void	rotate_player(t_player *player, double rot_angle)
{
	player->angle += rot_angle;
	if (player->angle > PI * 2)
		player->angle -= PI * 2;
	angle_to_vector(player);
}

int	quit_game(t_data *game)
{
	clean_up_mlx(game);
	cleanup_parser(game, SUCCESS);
	exit(0);
}
