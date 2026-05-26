#ifndef CUBE_H
#define CUBE_H
#include "../Libft/include/libft.h"
#include "MLX42/MLX42.h"
#include "error.h"
#include "parsing.h"

// Minimap colors
#define MINIMAP_WALL_RGB 184, 134, 11	// Amarillo ocre oscuro
#define MINIMAP_WALL_OPAQUE 255
#define MINIMAP_FLOOR_TRANSPARENT 0

// Minimap settings
#define MINIMAP_SCALE 5	// Escala de píxeles por celda del mapa

// Player minimap
#define PLAYER_COLOR_RGB 255, 0, 0	// Rojo para el jugador
#define PLAYER_SIZE 6	// Tamaño del cuadrado del jugador en píxeles

#ifndef ENABLE_LOGGER
# define ENABLE_LOGGER 1
#endif

#if ENABLE_LOGGER
# define LOG_FUNC() ft_printf("[LOG] %s\n", __func__)
#else
# define LOG_FUNC() ((void)0)
#endif

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
char	**read_map(char *map, t_data *data);



#endif
