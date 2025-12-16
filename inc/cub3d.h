/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/15 20:39:20 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# define ERROR 1
# define SUCCESS 0

# define RED 0
# define GREEN 1
# define BLUE 2
# define WIDTH 1620
# define HEIGHT 880

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

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	/* ... */
}	t_ray;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct texture
{	/* PATRICK */
	char	*north;				// cleanup_parser
	char	*south;				// cleanup_parser
	char	*west;				// cleanup_parser
	char	*east;				// cleanup_parser

	/* ELIAS   */
}	t_texture;


typedef struct flags
{
	/* PATRICK */
	bool	north;
	bool	south;
	bool	west;
	bool	east;
	bool	error;
	bool	ceiling;
	bool	floor;
	bool	in_map;
	bool	out_map;


	/* ELIAS   */
}	t_flag;


typedef struct rgb
{
	/* PATRICK */
	char *floor_string;
	char *ceil_string;
	char **ceiling;
	char **floor_split;
	int		ceil[3];
	int		floor[3];



	/* ELIAS   */
}	t_rgb;


typedef struct data
{
	/* PATRICK */
	bool		texture_pass;
	bool		color_pass;
	bool		map_pass;
	char		**map;

	t_texture	text;
	t_flag		flag;
	t_rgb		rgb;




	/* ELIAS   */
	void	*mlx;
	void	*mlx_win;
	t_img_data	*image;
	// char	**map;
	int	map_width;
	int	map_heigth;
	t_player	*player;
}	t_data;


# include "parser.h"
# include "render.h"
#endif
