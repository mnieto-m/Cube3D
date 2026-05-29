/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:45:24 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 17:45:51 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cube.h"
# include <math.h>

# define WIDTH 1024
# define HEIGHT 768

struct					s_data;
typedef struct s_data	t_data;

struct					s_player;
typedef struct s_player	t_player;

struct					s_path;
typedef struct s_path	t_path;

typedef enum e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}						t_orientation;

typedef struct s_game
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	double				last_time;
	mlx_texture_t		*tex_no;
	mlx_texture_t		*tex_so;
	mlx_texture_t		*tex_we;
	mlx_texture_t		*tex_ea;
	mlx_texture_t		*tex_floor;
	mlx_texture_t		*tex_ceil;
	mlx_image_t			*img_sprite;
	t_data				*data;
}						t_game;

typedef struct s_ray
{
	double				dir_x;
	double				dir_y;
	double				deltadist_x;
	double				deltadist_y;
	double				sidedist_x;
	double				sidedist_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	int					side;
	int					draw_start;
	int					draw_end;
	int					line_height;
	double				wall_dist;
	double				wall_x;
	int					tex_x;
}						t_ray;

int						exec(t_data *data);
void					render(void *param);
void					key_hook(mlx_key_data_t keydata, void *param);
void					move_player(t_game *game, t_data *data);
void					draw_ceiling(t_ray *ray, t_game *game, int x,
							t_data *data);
void					draw_floor(t_ray *ray, t_game *game, int x,
							t_data *data);
mlx_texture_t			*get_texture(t_ray *ray, t_game *game);
void					paint_wall(t_ray *ray, t_game *game, int x);
void					close_hook(void *param);
void					mlx_end(t_game *game);
void					put_pixel_fast(t_game *game, int x, int y,
							uint32_t color);

#endif
