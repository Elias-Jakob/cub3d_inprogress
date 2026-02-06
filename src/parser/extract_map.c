/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:09:04 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/06 17:22:00 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_map_chars(t_data *data, char *str, size_t map_y)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != SPACE && str[i] != TAB && str[i] != NEWLINE
			&& str[i] != '1' && str[i] != '0' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'W' && str[i] != 'E')
		{
			data->flag.in_map = false;
			return (print_error("Found invalid char", data, str[i]), 0);
		}
		else if (str[i] == 'N' || str[i] == 'S'
			|| str[i] == 'W' || str[i] == 'E')
		{
			if (set_player(data, str[i], map_y, i))
			{
				return (0);
			}
		}
		i++;
	}
	return (1);
}

char	**ft_realloc_map(char **map, size_t map_size)
{
	size_t		i;
	char	**tmp;

	tmp = ft_calloc(map_size + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < map_size - 1)
	{
		tmp[i] = ft_strdup(map[i]);
		if (!tmp[i])
			return (free_split(tmp), free_split(map), NULL);
		i++;
	}
	free_split(map);
	return (tmp);
}

int	check_empty_line(char *str)
{
	const char *line;

	line = (const char *) str;
	while (*line == 32 || *line == 9 || (*line > 10 && *line <= 13))
		line++;
	if (*line == '\n')
		return (ERROR);
	return (SUCCESS);
}

int	check_line_isprint(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

int	extract_map(t_data *data, char *line)
{
	static	size_t idx = 0;
	static	size_t id = 0;

	data->flag.in_map = true;
	if (!check_map_chars(data, line, id++))
		return (NOT_MY_LINE);
	if (check_empty_line(line))
	{
		data->flag.out_map = true;
		data->flag.in_map = false;
		return (FOUND);
	}
	if (data->flag.out_map && !check_line_isprint(line))
		return (print_error("Empty line in map\n", data, 0), 0);
	if (data->map.arr != NULL && *data->map.arr != NULL)
	{
		data->map.arr = ft_realloc_map(data->map.arr, idx + 1);
		if (!data->map.arr)
			return (print_error("Map realloc failed\n", data, 0), 0);
	}
	data->map.arr[idx++] = ft_strtrim(line, "\n");
	if (!data->map.arr[idx - 1])
		return (0);
	data->map.y = idx;
	return (FOUND);
}
