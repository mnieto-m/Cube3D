/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:41:57 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 17:41:58 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../Libft/include/libft.h"
# include "MLX42/MLX42.h"
# include "error.h"
# include "parsing.h"
# include "render.h"

typedef struct s_path
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor_color;
	int			ceiling_color;
}				t_path;

typedef struct s_player
{
	int			start_x;
	int			start_y;
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_data
{
	t_path		*path;
	char		**map;
	int			max_len;
	int			max_h;
	t_player	player;
}				t_data;

t_data			*init_data(char *str);
char			**read_map(char *map, t_data *data);

#endif
