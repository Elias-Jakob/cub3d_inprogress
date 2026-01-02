/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 05:34:13 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/30 15:52:18 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_coords(t_data *data)
{
	printf("%s Player\nStart coords:\tx:%f y:%f\n", OK_MSG, \
		data->player->x, data->player->y);
	printf("\n");
	printf("%s Map\nCoords:\t\tX: 0-%zu Y: 0-%zu\n", OK_MSG, data->map.x - 1,  \
		data->map.y - 1);
	printf("Size:\t\t%zu x %zu = %zu tiles\n\n", data->map.x,  \
		data->map.y, data->map.y*data->map.x);
	return ;
}

void	print_map(t_data *data)
{
	int i;

	i = 0;
	printf("\n%s Map extraction\n", OK_MSG);
	while (data->map.arr[i])
	{
		printf("[%i]\t\t%s\n", i, data->map.arr[i]);
		i++;
	}
	printf("\n");
	return ;
}

void	print_texture(t_data *data)
{
	printf("\n%s Texture extraction\n", OK_MSG);
	printf("\tNORTH: %s\n", data->text.north);
	printf("\tSOUTH: %s\n", data->text.south);
	printf("\tWEST: %s\n", data->text.west);
	printf("\tEAST: %s\n", data->text.east);
	return ;
}

void	print_rgb(t_data *data)
{
	int *ceil;
	int *floor;

	ceil = data->rgb.ceil;
	floor = data->rgb.floor;

	printf("\n%s RGB extraction\n", OK_MSG);
	printf("\tCeiling_string: %s", data->rgb.ceil_string);
	printf("\tRED: %i | GREEN: %i | BLUE: %i\n", \
		ceil[RED], ceil[GREEN], ceil[BLUE]);
	printf("\tFloor_string: %s", data->rgb.floor_string);
	printf("\tRED: %i | GREEN: %i | BLUE: %i\n", \
		floor[RED], floor[GREEN], floor[BLUE]);
	return ;
}
