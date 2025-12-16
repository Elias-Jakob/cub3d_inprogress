/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:54:53 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/16 05:52:43 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	extract_line_content(t_data *data, char *line)
{
	if (check_empty_line(line) && !data->flag.in_map)
		return (SUCCESS);
	else if (!data->texture_pass && extract_texture(data, line))
		return (ERROR);
	else if (!data->color_pass && extract_rgb(data, line))
		return (ERROR);
	else if (data->color_pass && data->texture_pass && extract_map(data, line))
	{
		data->flag.error = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	extract_files(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (printf("\033[31mError\033[0m\nMap empty\n"), ERROR);
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
	if(data->flag.error)
		return (ERROR);
	else if (!data->texture_pass || !data->color_pass)
		return (printf("\033[31mError\033[0m\nParsing not completed\n"), ERROR);
	else if (VERBOSE)
		print_map(data);
	return (SUCCESS);
}
