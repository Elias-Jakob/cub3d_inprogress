/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:15:17 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/15 18:11:23 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_north(t_data *data, const char *line)
{
	data->text.north = ft_strtrim(line, " \n\t");
	if (!data->text.north || ft_strcheck_spaces(data->text.north))
	{
		printf("\033[31mError\033[0m\nFailed to extract north texture\n");
		data->flag.error = true;
		return ;
	}
	data->flag.north = true;
	if (VERBOSE)
		printf("\tNORTH: %s\n", data->text.north);
}

static void	set_south(t_data *data, const char *line)
{
	data->text.south = ft_strtrim(line, " \n\t");
	if (!data->text.south || ft_strcheck_spaces(data->text.south))
	{
		printf("\033[31mError\033[0m\nFailed to extract south texture\n");
		data->flag.error = true;
		return ;
	}
	data->flag.south = true;
	if (VERBOSE)
		printf("\tSOUTH: %s\n", data->text.south);
}

static void	set_west(t_data *data, const char *line)
{
	data->text.west = ft_strtrim(line, " \n\t");
	if (!data->text.west || ft_strcheck_spaces(data->text.west))
	{
		printf("\033[31mError\033[0m\nFailed to extract west texture\n");
		data->flag.error = true;
		return ;
	}
	data->flag.west = true;
	if (VERBOSE)
		printf("\tWEST: %s\n", data->text.west);
}

static void	set_east(t_data *data, const char *line)
{
	data->text.east = ft_strtrim(line, " \n\t");
	if (!data->text.east || ft_strcheck_spaces(data->text.east))
	{
		printf("\033[31mError\033[0m\nFailed to extract east texture\n");
		data->flag.error = true;
		return ;
	}
	data->flag.east = true;
	if (VERBOSE)
		printf("\tEAST: %s\n", data->text.east);
}

int	extract_texture(t_data *data, const char *line)
{
	t_flag	flag;

	flag = data->flag;
	ft_skip_whitespaces(&line);
	if (ft_memcmp("NO", line, 3) == -32)
		set_north(data, &line[2]);
	else if (ft_memcmp("SO", line, 3) == -32)
		set_south(data, &line[2]);
	else if (ft_memcmp("WE", line, 3) == -32)
		set_west(data, &line[2]);
	else if (ft_memcmp("EA", line, 3) == -32)
		set_east(data, &line[2]);
	if (flag.error == true)
		return (ERROR);
	if (flag.north == true && flag.south == true
		&& flag.west == true && flag.east == true)
	{
		data->texture_pass = true;
		if (VERBOSE)
			printf("\033[32mOK\033[0m Texture extraction\n");
	}
	return (SUCCESS);
}
