/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejakob <ejakob@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:19:30 by ejakob            #+#    #+#             */
/*   Updated: 2026/01/24 14:25:08 by ejakob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# ifndef DEFINES_H
# define DEFINES_H

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
# define MINIMAP_SIZE 181
# define MINIMAP_CENTER 90
# define TILE_SIZE_2D 10
# define N_TILES ((MINIMAP_SIZE / TILE_SIZE_2D) / 2)

# define MINIMAP_BG_COLOR 0x000000
# define MINIMAP_WALL_COLOR 0xFFFFFF
# define MINIMAP_GRID_COLOR 0x8a8686
# define MINIMAP_PLAYER_COLOR 0xFFFF00
# define MINIMAP_RAY_COLOR 0xFF0000

# define N_TEXTURES 4

# define STEP_SIZE 0.08
# define ROTATION_ANGLE 0.05 // ~2.8°

# define COLLISION_MARGIN 0.1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define PI 3.14159265

# define ERROR_MSG "\033[31mError\033[0m"
# define OK_MSG "\033[32mOK\033[0m"

# endif
