/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/16 05:54:00 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#define WHITESPACES " \n\t\r\v\f"

#include "cub3d.h"

int	parser(t_data *data, char *file);

// EXTRACT FILES
int		extract_files(t_data *data, int fd);
int		extract_texture(t_data *data, const char *line);
int		extract_rgb(t_data *data, const char *line);
int		extract_map(t_data *data, char *line);
int		check_empty_line(char *str);

//PARSE MAP
int	validate_map(t_data *data);

//VERBOSE
void	print_map(t_data *data);
void	print_texture(t_data *data);
void	print_rgb(t_data *data);

//CLEANUP PARSER
void	cleanup_parser(t_data *data, int exit_code);
void	free_split(char **split);

# endif
