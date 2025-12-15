/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:38:00 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/15 10:23:57 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_hidden_filetyp(char *str, int len)
{
	while (len > 0)
	{
		if (str[len] == '/' && str[len])
		len--;
	}
	return ;
}

int	check_file_extension(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 4)
		return (ERROR);
	if (str[0] == '.' || !check_hidden_filetyp(str, len))
	{
		printf("Error:\nHidden Files forbidden\n");
		return (ERROR);
	}
	if (!ft_memcmp(&str[len - 4], ".cub", 5) == 0)
	{
		printf("Error:\nwrong file extension\n");
		return(ERROR);
	}
	if (VERBOSE)
		printf("File extension OK\n");
	return (SUCCESS);
}

int	parser(t_data *data, char *file)
{
	int	i;
	int fd;

	(void)data;
	i = 0;
	if(!check_filetyp_extension(file))
		return (ERROR);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ERROR);

	while (get_next_line(fd))
	{

		i++;
	}
	return (SUCCESS);
}
