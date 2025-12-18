/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:09:55 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/18 13:24:11 by pjelinek         ###   ########.fr       */
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

static int	check_rgb_code(char **split, int *rgb)
{
	int	i;

	i = 0;

	if (!split[0] || !split[1] || !split[2])
		return (ERROR);
	while (split[i])
	{
		if (!digit_check(split[i]))
			return (ERROR);
		i++;
	}
	rgb[RED] = ft_atoi(split[RED]);
	rgb[GREEN] = ft_atoi(split[GREEN]);
	rgb[BLUE] = ft_atoi(split[BLUE]);
	if (split[3] != NULL
		|| (rgb[RED] < 0 || rgb[RED] > 255)
		|| (rgb[GREEN] < 0 || rgb[GREEN] > 255)
		|| (rgb[BLUE] < 0 || rgb[BLUE] > 255))
	{
		return (ERROR);
	}
	return (SUCCESS);
}

static int extract_floor_rgb(t_data *data, const char *line)
{
	data->rgb.floor_string = ft_strtrim(line, WHITESPACES);
	if (!data->rgb.floor_string || !*data->rgb.floor_string)
		return (print_error("Malloc failed in flooring rgb code\n", data), ERROR);
	if (ft_count_char(data->rgb.floor_string, COMMA) >= 3)
		return (print_error("Too many commas found\n", data), ERROR);
	data->rgb.floor_split = ft_split(data->rgb.floor_string, ',');
	if (!data->rgb.floor_split) // !*data->rgb.flooring
		return(print_error("ft_split failed in flooring rgb code", data), ERROR);
	if (check_rgb_code(data->rgb.floor_split, data->rgb.floor))
		return(print_error("RBG code out of scope", data), ERROR);
	data->flag.floor = true;
	return (SUCCESS);
}

static int	extract_ceiling_rgb(t_data *data, const char *line)
{
	data->rgb.ceil_string = ft_strtrim(line, WHITESPACES);
	if (!data->rgb.ceil_string || !*data->rgb.ceil_string)
		return (print_error("Malloc failed in ceiling rgb code\n", data), ERROR);
	if (ft_count_char(data->rgb.ceil_string, COMMA) >= 3)
		return (print_error("Too many commas found\n", data), ERROR);
	data->rgb.ceiling = ft_split(data->rgb.ceil_string, ',');
	if (!data->rgb.ceiling) // !*data->rgb.ceiling
		return(print_error("ft_split failed in ceiling rgb code", data), ERROR);
	if (check_rgb_code(data->rgb.ceiling, data->rgb.ceil))
		return(print_error("RBG code out of scope", data), ERROR);
	data->flag.ceiling = true;
	return (SUCCESS);
}

int	extract_rgb(t_data *data, const char *line)
{
	t_flag	*flag;

	flag = &data->flag;
	ft_skip_whitespaces(&line);
	if (!flag->ceiling && (ft_memcmp("C ", line, 2) == 0
		|| ft_memcmp("C\t", line, 2) == 0))
		extract_ceiling_rgb(data, &line[1]);
	else if (!flag->floor && (ft_memcmp("F ", line, 2) == 0
		|| ft_memcmp("F\t", line, 2) == 0))
		extract_floor_rgb(data, &line[1]);
	else
		return (NOT_MY_LINE);
	if (flag->error == true)
		return (0);
	if (flag->ceiling && flag->floor)
	{
		data->rgb_pass = true;
		if (VERBOSE)
			print_rgb(data);
	}
	return (FOUND);
}
