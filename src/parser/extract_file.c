/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:54:53 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/15 16:17:11 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_line_content(t_data *data, char *line)
{
	if (line[0] == '\n')
		return (SUCCESS);
	else if (!data->texture_pass && extract_texture(data, line))
		return (ERROR);
	else if (!data->color_pass && extract_rgb(data, line))
		return (ERROR);
	//printf("check line content: %s\n", line);

	if(data->flag.error == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	extract_file(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		/* if (VERBOSE)
			printf("check line: %s\n", line); */
		if(check_line_content(data, line))
		{
			free (line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (VERBOSE)
		printf("exit file extraction\n");
	if(data->flag.error == ERROR)
		return (ERROR);
	return (SUCCESS);
}
