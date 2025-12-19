/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:43:11 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/19 07:29:45 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	print_doubles(t_data *data, const char *str)
{
	t_flag f;

	f = data->flag;
	if (f.north && (ft_memcmp("NO ", str, 3) == 0
		|| ft_memcmp("NO\t", str, 3) == 0))
		return (print_error("North texture already extracted\n", data), SUCCESS);
	else if (f.south && (ft_memcmp("SO ", str, 3) == 0
		|| ft_memcmp("SO\t", str, 3) == 0))
		return (print_error("South texture already extracted\n", data), SUCCESS);
	else if (f.west && (ft_memcmp("WE ", str, 3) == 0
		|| ft_memcmp("WE\t", str, 3) == 0))
		return (print_error("West texture already extracted\n", data), SUCCESS);
	else if (f.east && (ft_memcmp("EA ", str, 3) == 0
		|| ft_memcmp("EA\t", str, 3) == 0))
		return (print_error("East texture already extracted\n", data), SUCCESS);
	else if (f.ceiling && (ft_memcmp("C ", str, 2) == 0
		|| ft_memcmp("C\t", str, 2) == 0))
		return (print_error("Ceiling RGB already extracted\n", data), SUCCESS);
	else if (f.floor && (ft_memcmp("F ", str, 2) == 0
		|| ft_memcmp("F\t", str, 2) == 0))
		return (print_error("Floor RGB already extracted\n", data), SUCCESS);
	return (ERROR);
}

void	print_error(char *str, t_data *data)
{
	printf("%s\n", ERROR_MSG);
	printf("%s", str);
	data->flag.error = true;
	return ;
}

void	print_rgb_error(t_data *data)
{
	t_flag flag;

	flag = data->flag;
	printf("\033[31mRGB erxtraction incomplete\033[0m\n");
	if (!flag.ceiling)
		printf("Ceiling RGB missing\n");
	if (!flag.floor)
		printf("Floor RGB missing\n");
}

void	print_text_error(t_data *data)
{
	t_flag flag;

	flag = data->flag;
	printf("\033[31mTexture extraction incomplete\033[0m\n");
	if (!flag.north)
		printf("North texture missing\n");
	if (!flag.south)
		printf("South texture missing\n");
	if (!flag.west)
		printf("West texture missing\n");
	if (!flag.east)
		printf("East texture missing\n");
}
