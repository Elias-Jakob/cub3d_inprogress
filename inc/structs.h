/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejakob <ejakob@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:21:54 by ejakob            #+#    #+#             */
/*   Updated: 2026/01/24 14:24:32 by ejakob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# ifndef STRUCTS_H
# define STRUCTS_H

typedef enum	e_action {
	NONE = 0,
	ROTATE_LEFT = XK_Left,
	ROTATE_RIGHT = XK_Right,
	MOVE_FORWARD = XK_w,
	MOVE_BACKWARD = XK_s,
	MOVE_LEFT = XK_d,
	MOVE_RIGHT = XK_a,
}	t_action;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	/*
	Player directions
		N 0/-1
		S 0/1
		W -1/0
		E 1/0
	*/
	long	start_time;
	double	full_rotation;
}	t_player;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	camera_x; // current x column normalized to direction vector
	double	dir_x; // ray direction vector
	double	dir_y;
	double	delta_dist_x; // ray length to travel one grid unit
	double	delta_dist_y;
	int	side; // was a NS or a EW wall hit?
	double	wall_dist_x; // the distance to the NEXT grid line position that is checked
	double	wall_dist_y;
	int		step_x; // Tells us in which direction we're moving through the map
	int		step_y;
	double	wall_dist;
}	t_ray;

typedef struct	s_minimap
{
	int	start_col;
	int	start_row;
	int	end_col;
	int	end_row;
	int	x;
	int	y;
	double	x_offset;
	double	y_offset;
	int	tile_color;
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_minimap;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct texture
{
	/* PATRICK */
	char	*path;
	/* parser init file type .png/.xpm */
	bool	is_png;

	/* ELIAS   */
	t_img_data	image;
	int	width;
	int	height;
}	t_texture;

typedef struct	s_column
{
	int	x;
	int	y;
	double	wall_x;
	int	line_height;
	int	y_start;
	int	y_end;
	int	tex_x;
	double	tex_y;
	double	y_step_size;
	t_texture	*tex;
}	t_column;

///////////////////////////////
/* PATRICK PARSER STRUCTS    */
///////////////////////////////

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
	int		ceil;
	int		floor;

	/* ELIAS   */
}	t_rgb;

typedef struct map
{
	/* PATRICK */
	char	**arr;
	char	*line;
	int		y;
	int		x;



	/* ELIAS   */
}	t_map;

typedef struct data
{
	/* PATRICK */
	bool		texture_pass;
	bool		rgb_pass;
	bool		map_pass;

	t_texture	text[N_TEXTURES];
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
	int	player_size;
	int	player_center;
	t_player	*player;
	unsigned long	last_time_rendered;
	t_action	turn_action;
	t_action	move_action;
}	t_data;

# endif
