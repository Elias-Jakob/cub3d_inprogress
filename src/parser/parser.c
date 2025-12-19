/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:38:00 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/19 07:54:55 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	ft_check_valid_chars(t_data *data, char *str, int c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && !ft_isdigit(*str) && *str != c)
			return (print_error("Non-digit char in RGB string\n", data), 5);
		if (*str == c)
			count++;
		str++;
	}
	if (count >= 3)
		print_error("Too many commas found\n", data);
	return (count);
}

int	check_spaces(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i][1] == SPACE)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

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
		printf("%s Hidden file check\n", OK_MSG);
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
		printf("%s\nHidden files forbidden\n", ERROR_MSG);
		return (ERROR);
	}
	if (!(ft_memcmp(&str[len - 4], ".cub", 5) == 0))
	{
		printf("%s\nWrong file extension\n", ERROR_MSG);
		return(ERROR);
	}
	if (VERBOSE)
		printf("%s File extension\n", OK_MSG);
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
		printf("%s\n", ERROR_MSG);
		perror(file);
		return (ERROR);
	}
	data->map.arr = ft_calloc(1 + 1, sizeof(char *));
	if (!data->map.arr || extract_files(data, fd) || validate_map(data))
	{
		close(fd);
		return (ERROR);
	}
	close(fd);
	if (VERBOSE)
		printf("%s exit parser\n", OK_MSG);
	return (SUCCESS);
}
