/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:15:17 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/12 14:06:45 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_north(t_data *data, const char *line)
{
	data->text[NORTH].path = ft_strtrim(line, WHITESPACES);
	if (!data->text[NORTH].path || !*data->text[NORTH].path
		|| ft_strcheck_spaces(data->text[NORTH].path))
	{
		printf("%s\nFailed to extract north texture\n", ERROR_MSG);
		data->flag.error = true;
		return ;
	}
	data->flag.north = true;
}

static void	set_south(t_data *data, const char *line)
{
	data->text[SOUTH].path = ft_strtrim(line, WHITESPACES);
	if (!data->text[SOUTH].path || !*data->text[SOUTH].path
		|| ft_strcheck_spaces(data->text[SOUTH].path))
	{
		printf("%s\nFailed to extract south texture\n", ERROR_MSG);
		data->flag.error = true;
		return ;
	}
	data->flag.south = true;
}

static void	set_west(t_data *data, const char *line)
{
	data->text[WEST].path = ft_strtrim(line, WHITESPACES);
	if (!data->text[WEST].path || !*data->text[WEST].path
		|| ft_strcheck_spaces(data->text[WEST].path))
	{
		printf("%s\nFailed to extract west texture\n", ERROR_MSG);
		data->flag.error = true;
		return ;
	}
	data->flag.west = true;
}

static void	set_east(t_data *data, const char *line)
{
	data->text[EAST].path = ft_strtrim(line, WHITESPACES);
	if (!data->text[EAST].path || !*data->text[EAST].path
		|| ft_strcheck_spaces(data->text[EAST].path))
	{
		printf("%s \nFailed to extract east texture\n", ERROR_MSG);
		data->flag.error = true;
		return ;
	}
	data->flag.east = true;
}

int	extract_texture(t_data *data, const char *line)
{
	t_flag	*flag;

	flag = &data->flag;
	ft_skip_whitespaces(&line);
	if (!flag->north && (ft_memcmp("NO ", line, 3) == 0
		|| ft_memcmp("NO\t", line, 3) == 0))
		set_north(data, &line[2]);
	else if (!flag->south && (ft_memcmp("SO ", line, 3) == 0
		|| ft_memcmp("SO\t", line, 3) == 0))
		set_south(data, &line[2]);
	else if (!flag->west && (ft_memcmp("WE ", line, 3) == 0
		|| ft_memcmp("WE\t", line, 3) == 0))
		set_west(data, &line[2]);
	else if (!flag->east && (ft_memcmp("EA ", line, 3) == 0
		|| ft_memcmp("EA\t", line, 3) == 0))
		set_east(data, &line[2]);
	else
		return (NOT_MY_LINE);
	if (flag->error == true)
		return (0);
	if (flag->north && flag->south && flag->west && flag->east)
	{
		data->texture_pass = true;
		if (VERBOSE)
			print_texture(data);
	}
	return (FOUND);
}
