#ifndef CUBE_H
#define CUBE_H
#include "../Libft/include/libft.h"
#include "MLX42/MLX42.h"
#include "error.h"
#include "parsing.h"

typedef struct s_path
{
	char *no;
	char *so;
	char *we;
	char *ea;
	int floor_color;
	int ceiling_color;
} t_path;

typedef struct s_player
{
	int start_x;
	int start_y;
}t_player;

typedef struct s_data
{
	t_path *path;
	char **map;
	int max_len;
	int max_h;
	t_player player;
} t_data;

t_data *init_data(char  *str);


#endif
