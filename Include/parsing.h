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

static const t_parsing_path texture_parsing_table[] = {
    {"NO", ID_NO, NULL},
    {"SO", ID_SO, NULL},
    {"WE", ID_WE, NULL},
    {"EA", ID_EA, NULL},
    {"F",  ID_F, NULL},
    {"C",  ID_C, NULL},
    {NULL, ID_UNKNOWN, NULL}
};



void	parse(t_data *data);
int validate_map(t_data *data);
int validate_textures(t_data *data);
int	parse_textures(t_data *data, char **lines);
void	normalize_map(t_data *data);



#endif