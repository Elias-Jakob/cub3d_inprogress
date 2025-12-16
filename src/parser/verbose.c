/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 05:34:13 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/16 05:54:59 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_map(t_data *data)
{
	int i;

	i = 0;
	printf("\n\033[32mOK\033[0m Map extraction\n");
	while (data->map[i])
	{
		printf("[%i]\t%s", i, data->map[i]);
		i++;
	}
	printf("\n");
	return ;
}

void	print_texture(t_data *data)
{
	printf("\n\033[32mOK\033[0m Texture extraction\n");
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

	printf("\n\033[32mOK\033[0m RGB extraction\n");
	printf("\tCeiling_string;: %s", data->rgb.ceil_string);
	printf("\tRED: %i GREEN: %i BLUE: %i\n", \
		ceil[RED], ceil[GREEN], ceil[BLUE]);
	printf("\tFloor_string: %s", data->rgb.floor_string);
	printf("\tRED: %i GREEN: %i BLUE: %i\n", \
		floor[RED], floor[GREEN], floor[BLUE]);
	return ;
}
