/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:16:36 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/17 13:26:14 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_split(char **split)
{
	int	i;

	i = 0;
	if (!split && !*split)
		return ;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	printf("LEN: %i\n", i);
	
}
