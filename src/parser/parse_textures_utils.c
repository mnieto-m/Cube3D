/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:39:29 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/06/02 14:28:23 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

void	skip_word(const char *line, int *i)
{
	while (line[*i] && !ft_isspace(line[*i]))
		(*i)++;
}

void	set_color(t_data *data, t_id eid, char *trim)
{
	if (eid == ID_F)
		data->path->floor_color = parsing_color(trim, data);
	else
		data->path->ceiling_color = parsing_color(trim, data);
	free(trim);
}

void	set_texture_path(t_data *data, t_id eid, char *trim)
{
	if (eid == ID_NO)
		data->path->no = trim;
	else if (eid == ID_SO)
		data->path->so = trim;
	else if (eid == ID_WE)
		data->path->we = trim;
	else if (eid == ID_EA)
		data->path->ea = trim;
	else
		free(trim);
}
