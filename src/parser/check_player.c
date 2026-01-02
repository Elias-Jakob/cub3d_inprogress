/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:48:43 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/02 14:10:55 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_direction(t_data *data, char c)
{
	data->player->dir_x = 0;
	data->player->dir_y = -1;
	if (c == 'N')
		data->flag.player_north = true;
	else if (c == 'S')
	{
		data->player->dir_x = 0;
		data->player->dir_y = 1;
		data->flag.player_south = true;
	}
	else if (c == 'W')
	{
		data->player->dir_x = -1;
		data->player->dir_y = 0;
		data->flag.player_west = true;
	}
	else if (c == 'E')
	{
		data->player->dir_x = 1;
		data->player->dir_y = 0;
		data->flag.player_east = true;
	}
	data->player->plane_x = -data->player->dir_y * 0.66;
	data->player->plane_y = data->player->dir_x * 0.66;
}

int	set_player(t_data *data, char c, size_t y_coord, size_t x_coord)
{
	if (data->flag.player_north && c == 'N')
		return(print_error("N - double apperance\n", data), ERROR);
	else if (data->flag.player_south && c == 'S')
		return(print_error("S - double apperance\n", data), ERROR);
	else if (data->flag.player_west && c == 'W')
		return(print_error("W - double apperance\n", data), ERROR);
	else if (data->flag.player_east && c == 'E')
		return(print_error("E - double apperance\n", data), ERROR);
	if (data->flag.player_set)
		return (print_error("2 Player positions found\n", data), ERROR);
	set_direction(data, c);
	if (y_coord == 0)
		return (print_error("Player position invalid\n", data), ERROR);
	data->player->y = y_coord + .5;
	data->player->x = x_coord + .5;
	data->flag.player_set = true;
	return (SUCCESS);
}
