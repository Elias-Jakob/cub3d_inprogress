/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:09:55 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/15 18:10:59 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	digit_check(char *split)
{
	const char *str;

	str = (const char *) split;
	while (str)
	{
		if (!ft_isdigit(*str))
			return (ERROR);
		str++;
	}
	return (SUCCESS);
}

static int	check_rgb_code(char **split)
{
	int	ceil[3];
	int	i;

	i = 0;
	while (split[i])
	{
		if (!digit_check(split[i]))
			return (ERROR);
		i++;
	}
	ceil[RED] = ft_atoi(split[RED]);
	ceil[GREEN] = ft_atoi(split[GREEN]);
	ceil[BLUE] = ft_atoi(split[BLUE]);
	if (VERBOSE)
		printf("\tRED: %i GREEN: %i BLUE: %i\n", \
			ceil[RED], ceil[GREEN], ceil[BLUE]);
	if (split[3] != NULL || (ceil[RED] < 0 || ceil[RED] > 255)
		|| (ceil[GREEN] < 0 || ceil[GREEN] > 255)
		|| (ceil[BLUE] < 0 || ceil[BLUE] > 255))
	{
		return (ERROR);
	}
	return (SUCCESS);
}

static void	extract_floor_rgb(t_data *data, const char *line)
{
	data->rgb.floor_string = ft_strtrim(line, " \n\t");
	if (!data->rgb.floor_string || ft_strcheck_spaces(data->rgb.floor_string))
	{
		printf("\033[31mError\033[0m\nFailed to extract floor rgb code\n");
		data->flag.error = true;
		return ;
	}
	if (VERBOSE)
		printf("\tFloor_string: %s", data->rgb.floor_string);
	data->rgb.floor = ft_split(data->rgb.floor_string, ',');
	if (!data->rgb.floor || check_rgb_code(data->rgb.floor))
	{
		printf("\033[31mError\033[0m\nextract rgb floor failed\n");
		data->flag.error = true;
		return ;
	}
	data->flag.floor = true;
}

static void	extract_ceiling_rgb(t_data *data, const char *line)
{
	data->rgb.ceil_string = ft_strtrim(line, " \n\t");
	if (!data->rgb.ceil_string || ft_strcheck_spaces(data->rgb.ceil_string))
	{
		printf("\033[31mError\033[0m\nFailed to extract ceiling rgb code\n");
		data->flag.error = true;
		return ;
	}
	if (VERBOSE)
		printf("\tCeiling_string;: %s", data->rgb.ceil_string);
	data->rgb.ceiling = ft_split(data->rgb.ceil_string, ',');
	if (!data->rgb.ceiling || check_rgb_code(data->rgb.ceiling))
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
			printf("\033[32mOK\033[0m RGB extraction\n");
	}

	return (SUCCESS);
}
