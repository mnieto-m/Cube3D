#ifndef PARSING_H
#define PARSING_H

#include "../Include/cube.h"

struct s_data;
typedef struct s_data t_data;

typedef enum e_id
{
    ID_NO,
    ID_SO,
    ID_WE,
    ID_EA,
    ID_F,
    ID_C,
    ID_UNKNOWN
} t_id;

typedef struct s_parsing_path
{
    char *id;
    t_id	eid;                 // "NO", "SO", etc.
    void (*func)(char *line);        // función
} t_parsing_path;

const t_parsing_path	table[] = {
    {"NO", ID_NO},
    {"SO", ID_SO},
    {"WE", ID_WE},
    {"EA", ID_EA},
    {"F",  ID_F},
    {"C",  ID_C},
    {NULL, ID_UNKNOWN}
};



void	parse(t_data *data, char *map);
int validate_map(t_data *data);
int	parse_textures(t_data *data, char **lines);
void	normalize_map(t_data *data);



#endif