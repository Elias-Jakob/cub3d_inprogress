/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 04:19:52 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/18 18:46:31 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* void	replace_whitespaces(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->map[i])
	{

		i++;
	}
	return ;
} */

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
	//replace_whitespaces(data);
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
