#ifndef RENDER_H
#define RENDER_H

#include <math.h>
#include "../Libft/include/libft.h"
#include "MLX42/MLX42.h"

#define WIDTH   1024
#define HEIGHT  512

typedef enum e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}   t_orientation;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	char			**map;
	double			last_time;
	t_path			path;
	mlx_texture_t	*tex_no;
	mlx_texture_t	*tex_so;
	mlx_texture_t	*tex_we;
	mlx_texture_t	*tex_ea;
	mlx_texture_t	*tex_floor;
	mlx_texture_t	*tex_ceil;
	mlx_image_t		*img_sprite;
}	t_game;

typedef struct	s_ray
{
	double	dir_x;
	double	dir_y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	wall_dist;
	double	wall_x;
	int		tex_x;
}   t_ray;

t_data				*init_data(char *str);
int					print_error(char *str, t_data *data);
void				free_main(void *structure);
void				find_player(char **map, t_player *player);
void				render(void *param);
void				key_hook(mlx_key_data_t keydata, void *param);
void 				move_player(t_game *game);
void				draw_ceiling(t_ray *ray, t_game	*game, int x);
void				draw_floor(t_ray *ray, t_game	*game, int x);
mlx_texture_t		*get_texture(t_ray *ray, t_game *game);
void				paint_wall(t_ray *ray, t_game *game, int x);
void				close_hook(void *param);
void				mlx_end(t_game *game);
void   				put_pixel_fast(t_game *game, int x, int y, uint32_t color);

#endif
