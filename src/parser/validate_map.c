/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 04:19:52 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/06 17:14:59 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	*ft_realloc_str(t_data *data, char *str)
{
	char	*tmp;
	size_t	i;

	tmp = ft_calloc(data->map.x + 1, sizeof(char));
	if (!tmp)
		return (print_error("ft_calloc fail in validate map", data, 0), NULL);
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	free(str);
	return (tmp);
}

static void	replace_whitespaces(t_data *data)
{
	int i;
	int	j;
	int	len;

	i = 0;
	while (data->map.arr[i])
	{
		len = ft_strlen(data->map.arr[i]);
		if (len < data->map.x)
		{
			data->map.arr[i] = ft_realloc_str(data, data->map.arr[i]);
			if (!data->map.arr[i])
				cleanup_parser(data, ERROR);
		}
		j = 0;
		while (j < data->map.x)
		{
			if (data->map.arr[i][j] == TAB || data->map.arr[i][j] == '\0')
				data->map.arr[i][j] = SPACE;
			j++;
		}
		i++;
	}
}

static int	trim_line(char *str, int *len)
{
	while (*len - 1 > 0 && (str[*len - 1] == SPACE || str[*len - 1] == TAB))
		(*len)--;
	return (1);
}

void	set_x_coord(t_data *data)
{
	int		i;
	int		len_x;
	char	**map;

	i = 0;
	map = data->map.arr;
	while (map[i])
	{
		len_x = ft_strlen(map[i]);
		if (trim_line(map[i], &len_x) && len_x > data->map.x)
		{
			data->map.x = len_x;
		}
		i++;
	}
}


int	validate_map(t_data *data)
{
	if (data->map.x == 0 && data->map.y == 0)
		return (print_error("No Map in file\n", data, 0), ERROR);
	if (VERBOSE)
		print_map(data);
	set_x_coord(data);
	if (VERBOSE)
		print_map_coords(data);
	replace_whitespaces(data);
	if (VERBOSE)
		print_normalized_map(data);
	if (create_padding_map(data, data->map))
		return (ERROR);

	return (SUCCESS);
}
