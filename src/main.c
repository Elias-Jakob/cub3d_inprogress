/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2025/12/19 12:59:36 by pjelinek         ###   ########.fr       */
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
		print_error("Malloc failed\n", data);
		cleanup_parser(data, ERROR);
	}

}

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (printf("%s\nInvalid number of arguments\n", ERROR_MSG));
	init_data(&data);


	if (parser(&data, av[1]))
	{
		if (VERBOSE)
			printf("%s exit\n", ERROR_MSG);
		cleanup_parser(&data, ERROR);
		return (1);
	}


	/*
	==365405==	  Invalid write of size 4
	==365405==    at 0x4041FC: ft_put_pixel (utils.c:19)
	==365405==    by 0x403D17: draw_player (render.c:79)
	==365405==    by 0x403E56: render_game (render.c:104)
	==365405==    by 0x4038BE: render (init.c:27)
	==365405==    by 0x401395: main (main.c:40)
	==365405==  Address 0x514ad94 is 3,848,948 bytes inside an
	unallocated block of size 3,861,824 in arena "client"
	*/


/*
	if (!render(&data))
	printf("%s\n", ERROR_MSG);
	printf("%s", str);
	data->flag.error = true;
	return ;
		print_error("Init MLX failed\n", &data); */

	// TODO: somehow player and image are leaking even if i free them

	/////PATRICK
	if (VERBOSE)
		printf("%s exit\n", OK_MSG);
	cleanup_parser(&data, SUCCESS);
	return (0);
}




