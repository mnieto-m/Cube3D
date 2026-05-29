/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:35:26 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 17:54:04 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"



static void	is_duplicate(t_data *data, t_id eid)
{
	if (eid == ID_NO && data->path->no)
		print_error("INVALID MAP: duplicate NO identifier", data);
	else if (eid == ID_SO && data->path->so)
		print_error("INVALID MAP: duplicate SO identifier", data);
	else if (eid == ID_WE && data->path->we)
		print_error("INVALID MAP: duplicate WE identifier", data);
	else if (eid == ID_EA && data->path->ea)
		print_error("INVALID MAP: duplicate EA identifier", data);
	else if (eid == ID_F && data->path->floor_color != -1)
		print_error("INVALID MAP: duplicate F identifier", data);
	else if (eid == ID_C && data->path->ceiling_color != -1)
		print_error("INVALID MAP: duplicate C identifier", data);
}

static int	match_id(const char *line, const char *id)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(id);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (ft_strncmp(line, id, len) == 0 && (line[len] == ' '
			|| line[len] == '\t'));
}

static t_id	get_id_from_line(const char *line, const t_parsing_path *table)
{
	int	j;

	j = 0;
	while (table[j].id)
	{
		if (match_id(line, table[j].id))
			return (table[j].eid);
		j++;
	}
	return (ID_UNKNOWN);
}

static void	parse_line(t_data *data, t_id eid, char *line)
{
	int		i;
	char	*trim;

	i = 0;
	is_duplicate(data, eid);
	skip_spaces(line, &i);
	skip_word(line, &i);
	skip_spaces(line, &i);
	trim = ft_strtrim(&line[i], " \t");
	if (eid == ID_NO)
		data->path->no = trim;
	else if (eid == ID_SO)
		data->path->so = trim;
	else if (eid == ID_WE)
		data->path->we = trim;
	else if (eid == ID_EA)
		data->path->ea = trim;
	else if (eid == ID_F)
		data->path->floor_color = parsing_color(trim, data);
	else if (eid == ID_C)
		data->path->ceiling_color = parsing_color(trim, data);
	else
		free(trim);
}

int	parse_textures(t_data *data, char **lines)
{
	int		i;
	t_id	eid;
    
static const t_parsing_path texture_parsing_table[] = 
{
    {"NO", ID_NO, NULL},
    {"SO", ID_SO, NULL},
    {"WE", ID_WE, NULL},
    {"EA", ID_EA, NULL},
    {"F",  ID_F, NULL},
    {"C",  ID_C, NULL},
    {NULL, ID_UNKNOWN, NULL}
};
	i = 0;
	while (lines[i])
	{
		eid = get_id_from_line(lines[i], texture_parsing_table);
		if (eid != ID_UNKNOWN)
			parse_line(data, eid, lines[i]);
		i++;
	}
	validate_textures(data);
	return (0);
}
