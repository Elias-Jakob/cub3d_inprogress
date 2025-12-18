/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2025/12/16 05:37:26 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (printf("\033[31mError\033[0m\nInvalid number of arguments\n"));
	ft_memset(&data, 0, sizeof(t_data));
	if (parser(&data, av[1]))
	{
		printf("\033[31mERROR EXIT\033[0m\n");
		cleanup_parser(&data, ERROR);
		return (1);
	}
	printf("\033[32mOK EXIT\033[0m\n");
	/* Messy renderer stuff */
	free_split(data.map);
	data.map = (char **)malloc(sizeof(char *) * 11);
	data.map[0] = ft_strdup("1111111111");
	data.map[1] = ft_strdup("1010000001");
	data.map[2] = ft_strdup("100000S001");
	data.map[3] = ft_strdup("1000000001");
	data.map[4] = ft_strdup("1000000001");
	data.map[5] = ft_strdup("1000000001");
	data.map[6] = ft_strdup("1000010001");
	data.map[7] = ft_strdup("1000010001");
	data.map[8] = ft_strdup("1000010001");
	data.map[9] = ft_strdup("1111111111");
	data.map[10] = NULL;
	data.map_width = 10;
	data.map_heigth = 10;
	// init player
	data.player = (t_player *)malloc(sizeof(t_player));
	data.image = (t_img_data *)malloc(sizeof(t_img_data));
	if (!data.player || !data.image)
		printf("malloc failed\n");
	else
	{
		//-1 0 1
		//   |  1
		// -----0
		//   | -1
		ft_memset(data.player, 0, sizeof(t_player));
		data.player->x = 7 * 32;
		data.player->y = 3 * 32;
		data.player->dir_x = 0;
		data.player->dir_y = -1;
		render(&data);
	}
	free(data.player);
	free(data.image);
	// TODO: somehow player and image are leaking even if i free them
	cleanup_parser(&data, SUCCESS);
	return (0);
}
