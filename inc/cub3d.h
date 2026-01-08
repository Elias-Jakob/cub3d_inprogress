/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/07 08:02:55 by pjelinek         ###   ########.fr       */
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
# define MINIMAP_SIZE 160
# define MINIMAP_CENTER 80
# define MINIMAP_GRID_COLOR 0x8a8686
# define TILE_2D 16

# define COLLISION_MARGIN 0.1

# define PI 3.14159265

#define ERROR_MSG "\033[31mError\033[0m"
#define OK_MSG "\033[32mOK\033[0m"



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
# include <math.h>
# include "libft/libft.h"










///////////////////////////////
/* ELIAS EXECUTION STRUCTS   */
///////////////////////////////
typedef struct s_player
{
	double		x;
	double		y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	/*
	Player directions
		N 0/1
		S 0/-1
		W -1/0
		E 1/0
	*/
}	t_player;

typedef struct s_ray
{
	int		col;
	bool	hit;
	int		map_x;
	int		map_y;
	double	camera_x; // current x column normalized to direction vector
	double	dir_x; // ray direction vector
	double	dir_y;
	double	delta_dist_x; // ray length to travel one grid unit
	double	delta_dist_y;
	bool	side; // was a NS or a EW wall hit?
	double	side_dist_x; // the distance to the NEXT grid line position that is checked
	double	side_dist_y;
	int		step_x; // Tells us in which direction we're moving through the map
	int		step_y;
}	t_ray;

typedef struct	s_minimap
{
	int	start_col;
	int	start_row;
	int	end_col;
	int	end_row;
	int	x;
	int	y;
}	t_minimap;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;



///////////////////////////////
/* PATRICK PARSER STRUCTS    */
///////////////////////////////
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
	bool	player_set;
	bool	player_north;
	bool	player_south;
	bool	player_west;
	bool	player_east;


	/* ELIAS   */
}	t_flag;


typedef struct rgb
{
	/* PATRICK */
	char *floor_string;
	char *ceil_string;
	char **ceil_split;
	char **floor_split;
	int		ceil[3];
	int		floor[3];



	/* ELIAS   */
}	t_rgb;

typedef struct map
{
	/* PATRICK */
	char	**arr;
	char	*line;
	ssize_t	y;
	ssize_t	x;



	/* ELIAS   */
}	t_map;

typedef struct data
{
	/* PATRICK */
	bool		texture_pass;
	bool		rgb_pass;
	bool		map_pass;

	t_texture	text;
	t_flag		flag;
	t_rgb		rgb;
	t_map		map;



	/* ELIAS   */
	void	*mlx;
	void	*mlx_win;
	t_img_data	*image;
	// char	**map;
	int	map_width;
	int	map_height;
	t_player	*player;
}	t_data;


# include "parser.h"
# include "render.h"

#endif
