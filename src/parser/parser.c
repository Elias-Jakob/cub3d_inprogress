/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:38:00 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/16 05:54:09 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_hidden_filetyp(char *str, int len)
{
	while (len > 0)
	{
		if (str[len] == '/' && str[len + 1] == '.')
		{
			return (ERROR);
		}
		len--;
	}
	if (VERBOSE)
		printf("\033[32mOK\033[0m Hidden file check\n");
	return (SUCCESS);
}

static int	valid_file(char *str)
{
	size_t	len;

	if (!str)
		return (ERROR);
	len = ft_strlen(str);
	if (len <= 4)
		return (ERROR);
	if (str[0] == '.' || check_hidden_filetyp(str, len))
	{
		printf("\033[31mError\033[0m\nHidden files forbidden\n");
		return (ERROR);
	}
	if (!(ft_memcmp(&str[len - 4], ".cub", 5) == 0))
	{
		printf("\033[31mError\033[0m\nWrong file extension\n");
		return(ERROR);
	}
	if (VERBOSE)
		printf("\033[32mOK\033[0m File extension\n");
	return (SUCCESS);
}

int	parser(t_data *data, char *file)
{
	int fd;

	if(valid_file(file))
		return (ERROR);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("\033[31mError\033[0m\n");
		perror(file);
		return (ERROR);
	}
	data->map = ft_calloc(2, sizeof(char *));
	if (!data->map || extract_files(data, fd) || validate_map(data))
	{
		close(fd);
		return (ERROR);
	}
	close(fd);
	if (VERBOSE)
		printf("\033[32mOK\033[0m exit parser\n");
	return (SUCCESS);
}
