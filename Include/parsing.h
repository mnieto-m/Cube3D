/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:43:07 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/06/02 14:27:42 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../Include/cube.h"

struct					s_data;
typedef struct s_data	t_data;

typedef enum e_id
{
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_F,
	ID_C,
	ID_UNKNOWN
}						t_id;

typedef struct s_parsing_path
{
	char				*id;
	t_id				eid;
	void				(*func)(char *line);
}						t_parsing_path;

void					parse(t_data *data);
int						validate_map(t_data *data);
int						validate_textures(t_data *data);
int						parse_textures(t_data *data, char **lines);
void					normalize_map(t_data *data);
int						parsing_color(const char *line, t_data *data);
void					skip_word(const char *line, int *i);
void					skip_spaces(const char *line, int *i);
void					set_color(t_data *data, t_id eid, char *trim);
void					set_texture_path(t_data *data, t_id eid, char *trim);

#endif