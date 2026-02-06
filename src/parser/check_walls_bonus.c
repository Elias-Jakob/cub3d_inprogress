/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:38:26 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/06 17:12:17 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	flood_fill(char **pad_map, t_data *data, int x, int y)
{
	if (data->flag.error)
		return ;
	if (x < 0 || y < 0  || x >= data->map.x + 2 || y >= data->map.y + 2
		|| pad_map[y][x] == '1'	|| pad_map[y][x] == 'X')
		return ;
	if (pad_map[y][x] == '0' || pad_map[y][x] == 'N'
		|| pad_map[y][x] == 'S' || pad_map[y][x] == 'W'
		|| pad_map[y][x] == 'E' || pad_map[y][x] == 'D')
	{
		data->flag.error = true;
		printf("%s\nMap not proper walled\n", ERROR_MSG);
		return ;
	}
	else
	{
		pad_map[y][x] = 'X';
		flood_fill(pad_map, data, x + 1, y);
		flood_fill(pad_map, data, x - 1, y);
		flood_fill(pad_map, data, x, y + 1);
		flood_fill(pad_map, data, x, y - 1);
	}
}

void	copy_map(t_map old_map, char **new_map)
{
	size_t	i;
	size_t	old_map_len;

	i = 0;
	while (old_map.arr[i])
	{
		old_map_len = ft_strlen(old_map.arr[i]);
		ft_memcpy(&new_map[i + 1][1], old_map.arr[i], old_map_len);
		i++;
	}
}

void	check_inner_walling(char **map, t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == SPACE)
			{
				flood_fill(map, data, j, i);
			}
			j++;
		}
		i++;
	}
}

int	create_padding_map(t_data *data, t_map map)
{
	char	**pad_map;
	int	i;

	pad_map = ft_calloc(map.y + 2 + 1, sizeof(char *));
	if (!pad_map)
		return (print_error("Calloc for pad_map failed\n", data, 0), ERROR);
	i = 0;
	while (i < map.y + 2)
	{
		pad_map[i] = ft_calloc(map.x + 2 + 1,  sizeof(char ));
		if (!pad_map[i])
		{
			free_split(pad_map);
			printf("Calloc for pad_map[%i] failed\n", i);
			return (ERROR);
		}
		ft_memset(pad_map[i], SPACE, map.x + 2);
		i++;
	}
	copy_map(map, pad_map);
	flood_fill(pad_map, data, 0, 0);
	check_inner_walling(pad_map, data);
	if (data->flag.error)
		return (free_split(pad_map), ERROR);
	return (free_split(pad_map), SUCCESS);
}
