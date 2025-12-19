/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:50:24 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/19 07:36:59 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	safe_free(char **arr)
{
	if (arr[RED])
		free(arr[RED]);
	if (arr[GREEN])
		free(arr[GREEN]);
	if (arr[BLUE])
		free(arr[BLUE]);
	return ;
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

void	cleanup_rgb(t_data *data)
{
	if (data->rgb.ceil_string)
		free(data->rgb.ceil_string);
	if (data->rgb.floor_string)
		free(data->rgb.floor_string);
	free_split(data->rgb.ceiling);
	free_split(data->rgb.floor_split);
	ft_memset(&data->rgb, 0, sizeof(t_rgb));
}

void	cleanup_textures(t_data *data)
{
	if (data->text.north)
	{
		free(data->text.north);
		data->text.north = NULL;
	}
	if (data->text.south)
	{
		free(data->text.south);
		data->text.south = NULL;
	}
	if (data->text.west)
	{
		free(data->text.west);
		data->text.west = NULL;
	}
	if (data->text.east)
	{
		free(data->text.east);
		data->text.east = NULL;
	}
}

void	cleanup_parser(t_data *data, int exit_code)
{
	if (data->player)
	{
		free(data->player);
		data->player = NULL;
	}
	if (data->image)
	{
		free(data->image);
		data->player = NULL;
	}
	cleanup_textures(data);
	cleanup_rgb(data);
	free_split(data->map.arr);
	exit(exit_code);
}
