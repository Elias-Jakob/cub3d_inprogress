/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2026/02/06 21:08:27 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->player = (t_player *)ft_calloc(1, sizeof(t_player));
	data->image = (t_img_data *)ft_calloc(1, sizeof(t_img_data));
	if (!data->player || !data->image)
	{
		print_error("Malloc failed\n", data, 0);
		cleanup_parser(data, ERROR);
	}
}

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (printf("%s\nInvalid number of arguments\n", ERROR_MSG));
	init_data(&data);
	if (parser(&data, av[1]) || !render(&data))
	{
		if (VERBOSE)
			printf("%s exit\n", ERROR_MSG);
		cleanup_parser(&data, ERROR);
	}
	if (VERBOSE)
		printf("%s exit\n", OK_MSG);
	cleanup_parser(&data, SUCCESS);
	return (0);
}




