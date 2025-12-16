/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:09:55 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/16 05:48:55 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	digit_check(char *split)
{
	while (split)
	{
		if (!ft_isdigit(*split))
			return (ERROR);
		split++;
	}
	return (SUCCESS);
}

static int	check_rgb_code(char **split, int *color)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (!digit_check(split[i]))
			return (ERROR);
		i++;
	}
	color[RED] = ft_atoi(split[RED]);
	color[GREEN] = ft_atoi(split[GREEN]);
	color[BLUE] = ft_atoi(split[BLUE]);
	if (split[3] != NULL || (color[RED] < 0 || color[RED] > 255)
		|| (color[GREEN] < 0 || color[GREEN] > 255)
		|| (color[BLUE] < 0 || color[BLUE] > 255))
	{
		return (ERROR);
	}
	return (SUCCESS);
}

static void	extract_floor_rgb(t_data *data, const char *line)
{

	data->rgb.floor_string = ft_strtrim(line, WHITESPACES);
	if (!data->rgb.floor_string || ft_strcheck_spaces(data->rgb.floor_string))
	{
		printf("\033[31mError\033[0m\nFailed to extract floor rgb code\n");
		data->flag.error = true;
		return ;
	}
	data->rgb.floor_split = ft_split(data->rgb.floor_string, ',');
	if (!data->rgb.floor_split
		|| check_rgb_code(data->rgb.floor_split, data->rgb.floor))
	{
		printf("\033[31mError\033[0m\nextract rgb floor failed\n");
		data->flag.error = true;
		return ;
	}
	data->flag.floor = true;
}

static void	extract_ceiling_rgb(t_data *data, const char *line)
{
	data->rgb.ceil_string = ft_strtrim(line, WHITESPACES);
	if (!data->rgb.ceil_string || ft_strcheck_spaces(data->rgb.ceil_string))
	{
		printf("\033[31mError\033[0m\nFailed to extract ceiling rgb code\n");
		data->flag.error = true;
		return ;
	}
	data->rgb.ceiling = ft_split(data->rgb.ceil_string, ',');
	if (!data->rgb.ceiling || check_rgb_code(data->rgb.ceiling, data->rgb.ceil))
	{
		printf("\033[31mError\033[0m\nextract rgb ceiling failed\n");
		data->flag.error = true;
		return ;
	}
	data->flag.ceiling = true;
}

int	extract_rgb(t_data *data, const char *line)
{
	t_flag	flag;

	flag = data->flag;
	ft_skip_whitespaces(&line);
	if (ft_memcmp("C", line, 2) == -32)
		extract_ceiling_rgb(data, &line[1]);
	else if (ft_memcmp("F", line, 2) == -32)
		extract_floor_rgb(data, &line[1]);
	if (data->flag.error == true)
		return (ERROR);
	if (flag.ceiling && flag.floor)
	{
		data->color_pass = true;
		if (VERBOSE)
			print_rgb(data);
	}
	return (SUCCESS);
}
