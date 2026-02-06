/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/06 17:11:32 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#define WHITESPACES " \n\t\r\v\f"
#define NOT_MY_LINE 0
#define FOUND 2
#define COMMA ','
#define SPACE ' '
#define TAB '\t'


#include "cub3d.h"

int	parser(t_data *data, char *file);

// EXTRACT FILES
int		extract_files(t_data *data, int fd);
int		extract_texture(t_data *data, const char *line);
int		extract_rgb(t_data *data, const char *line);
int		extract_map(t_data *data, char *line);
int		check_empty_line(char *str);
size_t	ft_check_valid_chars(t_data *data, char *str, int c);


//PARSE MAP
int		validate_map(t_data *data);
int		check_spaces(char **split);
int		check_player_flags(t_data *data, char c);
int		set_player(t_data *data, char c, size_t y_coord, size_t x_coord);
void	check_walling(t_data *data, t_map map, int x, int y);
int		create_padding_map(t_data *data, t_map map);



//VERBOSE
void	print_map(t_data *data);
void	print_texture(t_data *data);
void	print_rgb(t_data *data);

//CLEANUP PARSER
void	cleanup_parser(t_data *data, int exit_code);
void	free_split(char **split);
void	safe_free(char **arr);

//PRINT
void	print_text_rgb_error(t_data *data);
void	print_error(char *str, t_data *data, char flag);
int		print_doubles(t_data *data, const char *str);
void	print_map_coords(t_data *data);
void	print_normalized_map(t_data *data);



# endif
