/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:13:37 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/09 21:24:42 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_skip_spaces(const char **p)
{
	while (**p == 32 || (**p >= 9 && **p <= 13))
	{
		if (**p >= 9 && **p <= 13)
			return (false);
		(*p)++;
	}
	return (true);
}

int	ft_strcheck_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	digit_check(char *split)
{
	while (split)
	{
		if (!ft_isdigit(*split))
			return (ERROR);
		split++;
	}
	return (SUCCESS);
}
