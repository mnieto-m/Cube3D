#include "../Include/cube.h"

static void is_duplicate(t_data *data, t_id eid)
{
	//LOG_FUNC();
    if (eid == ID_NO && data->path->no)
        print_error("Identificador NO duplicado", data);
    else if (eid == ID_SO && data->path->so)
        print_error("Identificador SO duplicado", data);
    else if (eid == ID_WE && data->path->we)
        print_error("Identificador WE duplicado", data);
    else if (eid == ID_EA && data->path->ea)
        print_error("Identificador EA duplicado", data);
    else if (eid == ID_F && data->path->floor_color != 0)// falta pàrsear el color
        print_error("Identificador F duplicado", data);
    else if (eid == ID_C && data->path->ceiling_color != 0)// falta pàrsear el color
        print_error("Identificador C duplicado", data);
}
static int	match_id(const char *line, const char *id)
{
    int	len;

	//LOG_FUNC();
    len = ft_strlen(id);
    return (ft_strncmp(line, id, len) == 0
        && (line[len] == ' ' || line[len] == '\t'));
}

static t_id	get_id_from_line(const char *line, const t_parsing_path *table)
{
    int	j = 0;

	//LOG_FUNC();
    while (table[j].id)
    {
        if (match_id(line, table[j].id))
            return (table[j].eid);
        j++;
    }
    return (ID_UNKNOWN);
}

static void	parse_line(t_data *data, t_id eid, char *line, int i)
{
	//LOG_FUNC();
    is_duplicate(data, eid);
    if (eid == ID_NO)
        data->path->no = ft_strdup(line + 2);
    else if (eid == ID_SO)
        data->path->so = ft_strdup(line + 2);
    else if (eid == ID_WE)
        data->path->we = ft_strdup(line + 2);
    else if (eid == ID_EA)
        data->path->ea = ft_strdup(line + 2);
    else if (eid == ID_F)
        data->path->floor_color = 1; // Falta parsear el color
    else if (eid == ID_C)
        data->path->ceiling_color = 1; // Falta parsear el color
    else
    {
        print_error("Identificador desconocido", data);
    }
}

int	parse_textures(t_data *data, char **lines)
{
    static const t_parsing_path table[] = {
        {"NO", ID_NO, NULL},
        {"SO", ID_SO, NULL},
        {"WE", ID_WE, NULL},
        {"EA", ID_EA, NULL},
        {"F",  ID_F, NULL},
        {"C",  ID_C, NULL},
        {NULL, ID_UNKNOWN, NULL}
    };
    int i = 0;
    t_id eid;

	LOG_FUNC();
    while (lines[i]&& i )
    {
        eid = get_id_from_line(lines[i], table);
        parse_line(data, eid, lines[i], i);
        i++;
    }
    return (0);
}
