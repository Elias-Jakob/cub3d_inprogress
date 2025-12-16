/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:09:04 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/16 05:42:03 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

	data->flag.in_map = true;
	if (!data->flag.out_map && check_empty_line(line))
	{
		data->flag.out_map = true;
		return (SUCCESS);
	}
	if (data->flag.out_map && !check_line_isprint(line))
		return (printf("\033[31mError\033[0m\nEmpty line in map\n"), ERROR);
	if (line[0] == '\n')
		return (SUCCESS);
	if (data->map != NULL && *data->map != NULL)
	{
		data->map = ft_realloc_map(data->map, idx + 1);
		if (!data->map)
			return (printf("\033[31mError\033[0m\nMap realloc failed\n"), ERROR);

	}
	data->map[idx++] = ft_strdup(line);
	if (!data->map[idx - 1])
		return (ERROR);
	return (SUCCESS);
}
