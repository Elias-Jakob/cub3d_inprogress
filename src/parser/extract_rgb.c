/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:09:55 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/19 07:55:22 by pjelinek         ###   ########.fr       */
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
	int		i;
	char	*num[4];

	i = 0;
	ft_bzero(num, sizeof(num));
	if (!split[0] || !split[1] || !split[2] || split[3] != NULL)
		return (ERROR);
	while (split[i])
	{
		num[i] = ft_strtrim(split[i], WHITESPACES);
		if (!num[i] || !digit_check(num[i]) || ft_strcheck_spaces(num[i]))
			return (safe_free(num), ERROR);
		i++;
	}
	rgb[RED] = ft_atoi(num[RED]);
	rgb[GREEN] = ft_atoi(num[GREEN]);
	rgb[BLUE] = ft_atoi(num[BLUE]);
	free(num[RED]);
	free(num[GREEN]);
	free(num[BLUE]);
	if ((rgb[RED] < 0 || rgb[RED] > 255) || (rgb[GREEN] < 0 || rgb[GREEN] > 255)
		|| (rgb[BLUE] < 0 || rgb[BLUE] > 255))
		return (ERROR);
	return (SUCCESS);
}

static int extract_floor_rgb(t_data *data, const char *line)
{
	data->rgb.floor_string = ft_strtrim(line, WHITESPACES);
	if (!data->rgb.floor_string || !*data->rgb.floor_string)
		return (print_error("Malloc failed in flooring rgb code\n", data), ERROR);
	if (ft_check_valid_chars(data, data->rgb.floor_string, COMMA) >= 3)
		return (ERROR);
	data->rgb.floor_split = ft_split(data->rgb.floor_string, ',');
	if (!data->rgb.floor_split) // !*data->rgb.flooring
		return(print_error("ft_split failed in flooring rgb code\n", data), ERROR);
	if (check_rgb_code(data->rgb.floor_split, data->rgb.floor))
		return(print_error("RBG code out of scope\n", data), ERROR);
	data->flag.floor = true;
	return (SUCCESS);
}

static int	extract_ceiling_rgb(t_data *data, const char *line)
{
	data->rgb.ceil_string = ft_strtrim(line, WHITESPACES);
	if (!data->rgb.ceil_string || !*data->rgb.ceil_string)
		return (print_error("Malloc failed in ceiling rgb code\n", data), ERROR);
	if (ft_check_valid_chars(data, data->rgb.ceil_string, COMMA) >= 3)
		return (ERROR);
	data->rgb.ceil_split = ft_split(data->rgb.ceil_string, ',');
	if (!data->rgb.ceil_split) // !*data->rgb.ceiling
		return(print_error("ft_split failed in ceiling rgb code\n", data), ERROR);
	if (check_rgb_code(data->rgb.ceil_split, data->rgb.ceil))
		return(print_error("RBG code out of scope\n", data), ERROR);
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
