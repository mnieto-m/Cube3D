/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:42:25 by agnesgar          #+#    #+#             */
/*   Updated: 2026/05/29 17:34:43 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

#define MARGIN 0.5

void	move_vertically(t_game *game, double speed, t_data *data)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (data->map[(int)(data->player.y)][(int)(data->player.x
				+ data->player.dir_x * (speed + MARGIN))] != '1')
			data->player.x += data->player.dir_x * speed;
		if (data->map[(int)(data->player.y + data->player.dir_y * (speed
					+ MARGIN))][(int)(data->player.x)] != '1')
			data->player.y += data->player.dir_y * speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (data->map[(int)(data->player.y)][(int)(data->player.x
				- data->player.dir_x * (speed + MARGIN))] != '1')
			data->player.x -= data->player.dir_x * speed;
		if (data->map[(int)(data->player.y - data->player.dir_y * (speed
					+ MARGIN))][(int)(data->player.x)] != '1')
			data->player.y -= data->player.dir_y * speed;
	}
}

void	move_left_or_right(t_game *game, double olddir_x, double oldplane_x,
		double rot, t_data *data)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		data->player.dir_x = olddir_x * cos(-rot) - data->player.dir_y
			* sin(-rot);
		data->player.dir_y = olddir_x * sin(-rot) + data->player.dir_y
			* cos(-rot);
		data->player.plane_x = oldplane_x * cos(-rot) - data->player.plane_y
			* sin(-rot);
		data->player.plane_y = oldplane_x * sin(-rot) + data->player.plane_y
			* cos(-rot);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		data->player.dir_x = olddir_x * cos(rot) - data->player.dir_y
			* sin(rot);
		data->player.dir_y = olddir_x * sin(rot) + data->player.dir_y
			* cos(rot);
		oldplane_x = data->player.plane_x;
		data->player.plane_x = oldplane_x * cos(rot) - data->player.plane_y
			* sin(rot);
		data->player.plane_y = oldplane_x * sin(rot) + data->player.plane_y
			* cos(rot);
	}
}

void	move_horizontally(t_game *game, double speed, t_data *data)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (data->map[(int)(data->player.y)][(int)(data->player.x
				+ data->player.dir_y * (speed + MARGIN))] != '1')
			data->player.x += data->player.dir_y * speed;
		if (data->map[(int)(data->player.y - data->player.dir_x * (speed
					+ MARGIN))][(int)(data->player.x)] != '1')
			data->player.y -= data->player.dir_x * speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (data->map[(int)(data->player.y)][(int)(data->player.x
				- data->player.dir_y * (speed + MARGIN))] != '1')
			data->player.x -= data->player.dir_y * speed;
		if (data->map[(int)(data->player.y + data->player.dir_x * (speed
					+ MARGIN))][(int)(data->player.x)] != '1')
			data->player.y += data->player.dir_x * speed;
	}
}

void	move_player(t_game *game, t_data *data)
{
	double	speed;
	double	olddir_x;
	double	oldplane_x;
	double	rot;

	speed = (mlx_get_time() - game->last_time) * 3.0;
	game->last_time = mlx_get_time();
	olddir_x = data->player.dir_x;
	oldplane_x = data->player.plane_x;
	rot = speed * 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx,
			MLX_KEY_W))
		move_vertically(game, speed, data);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) || mlx_is_key_down(game->mlx,
			MLX_KEY_RIGHT))
		move_left_or_right(game, olddir_x, oldplane_x, rot, data);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D) || mlx_is_key_down(game->mlx,
			MLX_KEY_A))
		move_horizontally(game, speed, data);
}
