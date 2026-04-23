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
    if (!line)
        return (0);
    // Skip leading whitespace
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
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

static void	parse_line(t_data *data, t_id eid, char *line)
{
	char	*start;

	//LOG_FUNC();
    if (eid == ID_UNKNOWN)
        return;  // Skip lineas vacías y de mapa
    is_duplicate(data, eid);
    
    // Skip leading whitespace and ID
    start = line;
    while (*start && (*start == ' ' || *start == '\t'))
        start++;
    // Skip the ID (2 or 1 character)
    while (*start && *start != ' ' && *start != '\t')
        start++;
    // Skip whitespace after ID
    while (*start && (*start == ' ' || *start == '\t'))
        start++;
    
    if (eid == ID_NO)
        data->path->no = ft_strdup(start);
    else if (eid == ID_SO)
        data->path->so = ft_strdup(start);
    else if (eid == ID_WE)
        data->path->we = ft_strdup(start);
    else if (eid == ID_EA)
        data->path->ea = ft_strdup(start);
    else if (eid == ID_F)
        data->path->floor_color = 1; // Falta parsear el color
    else if (eid == ID_C)
        data->path->ceiling_color = 1; // Falta parsear el color
}

static int	is_config_line(const char *line)
{
	if (!line || *line == '\0')
		return (0);
	return (match_id(line, "NO") || match_id(line, "SO") || 
	        match_id(line, "WE") || match_id(line, "EA") ||
	        match_id(line, "F") || match_id(line, "C"));
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
    int i;
    int found_map;
    int last_map_idx;
    t_id eid;
    char *p;

    i = 0;
    found_map = 0;
    last_map_idx = -1;
	LOG_FUNC();
    while (lines[i])
    {
        // Check if we found the map (a line starting with 0 or 1)
        if (!found_map && (lines[i][0] == '0' || lines[i][0] == '1'))
            found_map = 1;
        
        if (found_map && (lines[i][0] == '0' || lines[i][0] == '1'))
            last_map_idx = i;
        
        // If we found the map and this line is a config line, error!
        if (found_map && is_config_line(lines[i]))
            print_error("INVALID MAP: Configuration line after map", data);
        
        // If we found the map, check for non-empty lines that are not map content
        if (found_map && lines[i][0] != '\0')
        {
            p = lines[i];
            while (*p && (*p == ' ' || *p == '\t'))
                p++;
            // If line has content but doesn't start with 0 or 1, it's forbidden
            if (*p != '\0' && *p != '0' && *p != '1')
                print_error("INVALID MAP: Forbidden content after map", data);
        }
        
        eid = get_id_from_line(lines[i], table);
        parse_line(data, eid, lines[i]);
        i++;
    }
    
    // Check if there's content after the last map line
    if (last_map_idx >= 0 && lines[last_map_idx + 1])
        print_error("INVALID MAP: Content after map", data);
    
    return (0);
}
