/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 04:19:52 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/18 20:09:03 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*ft_realloc_str(t_data *data, char *str)
{
	char	*tmp;
	size_t	i;

	tmp = ft_calloc(data->map.x + 1, sizeof(char));
	if (!tmp)
		return (print_error("ft_calloc fail in validate map", data), NULL);
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	free(str);
	return (tmp);
}

void	replace_whitespaces(t_data *data)
{
	int i;
	int	j;
	int	len;

	i = 0;
	printf("HIIIIIIIIIII\n");

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
	print_map(data);
}

int	trim_line(char *str, ssize_t *len)
{
	while (*len - 1 > 0 && (str[*len - 1] == SPACE || str[*len - 1] == TAB))
		(*len)--;
	return (1);
}

void	set_x_coord(t_data *data)
{
	ssize_t	i;
	ssize_t	len_x;
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

void	normalize_map(t_data *data)
{
	set_x_coord(data);
	if (VERBOSE)
		print_coords(data);
	replace_whitespaces(data);
	return ;
}

int	validate_map(t_data *data)
{
	if (VERBOSE)
		print_map(data);
	normalize_map(data);
	/*if (!check_outside_walling(data))
		return (ERROR); */

	return (SUCCESS);
}
