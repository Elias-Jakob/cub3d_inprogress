/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2025/12/15 14:56:17 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (printf("\033[31mError\033[0m\nInvalid number of arguments\n"));
	ft_memset(&data, 0, sizeof(t_data));
	if (!parser(&data, av[1]))
	{
		cleanup_parser(&data);
		printf("FAILED Parser\n");
		return (1);
	}
	cleanup_parser(&data);
	return (0);
}
