/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/15 10:03:56 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H




# ifndef VERBOSE
#  define VERBOSE 0
# endif

# define ERROR 1
# define SUCCESS 0

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"







///////////////////////////////
/* PATRICK PARSER STRUCTS    */
///////////////////////////////


///////////////////////////////
/* ELIAS EXECUTION STRUCTS   */
///////////////////////////////



typedef struct data
{
	char			**envp;
	char			**env_copy;
	size_t			env_size;
	struct s_export	*export;
	size_t			export_size;
	int				last_exit_code;
}	t_data;


# include "parser.h"
#endif
