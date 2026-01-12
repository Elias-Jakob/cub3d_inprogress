/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:54:53 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/19 18:51:32 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	wrong_input(t_data *data, char *line)
{
	const char *str;

	str = line;
	ft_skip_whitespaces(&str);
	while (*str)
	{
		if (ft_isprint(*str))
		{
			data->flag.error = true;
			if (!print_doubles(data, str))
				return (ERROR);
			else
				printf("%s\nWrong input in line: %s\n", ERROR_MSG, str);
			return (ERROR);
		}
		str++;
	}
	return (SUCCESS);
}

static int	extract_line_content(t_data *data, char *line)
{
	if (!data->flag.in_map && check_empty_line(line))
		return (SUCCESS);
	else if (!data->texture_pass && extract_texture(data, line))
		return (SUCCESS);
	else if (!data->rgb_pass && extract_rgb(data, line))
		return (SUCCESS);
	else if (data->rgb_pass && data->texture_pass && extract_map(data, line))
		return (SUCCESS);
	else if (!data->flag.in_map && wrong_input(data, line))
		return (ERROR);
	return (ERROR);

}

int	extract_files(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (printf("%s\nMap empty\n", ERROR_MSG), ERROR);
	while (line)
	{
		if(extract_line_content(data, line))
		{
			free (line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!data->texture_pass || !data->rgb_pass)
		return (print_text_rgb_error(data), ERROR);
	else if(data->flag.error)
		return (ERROR);
	else if(!data->flag.player_set)
		return (print_error("Player not found on map\n", data), ERROR);
	return (SUCCESS);
}
