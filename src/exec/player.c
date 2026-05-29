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

#define M 0.5

void	move_vertically(t_game *game, double speed, t_data *data)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (data->map[(int)(data->player.y)]
			[(int)(data->player.x + data->player.dir_x * (speed + M))] != '1')
			data->player.x += data->player.dir_x * speed;
		if (data->map[(int)(data->player.y + data->player.dir_y * (speed + M))]
			[(int)(data->player.x)] != '1')
			data->player.y += data->player.dir_y * speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (data->map[(int)(data->player.y)]
			[(int)(data->player.x - data->player.dir_x * (speed + M))] != '1')
			data->player.x -= data->player.dir_x * speed;
		if (data->map[(int)(data->player.y - data->player.dir_y * (speed + M))]
			[(int)(data->player.x)] != '1')
			data->player.y -= data->player.dir_y * speed;
	}
}

void	move_lr(t_game *game, t_old *old, double r, t_data *data)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		data->player.dir_x = old->dir_x * cos(-r)
			- data->player.dir_y * sin(-r);
		data->player.dir_y = old->dir_x * sin(-r)
			+ data->player.dir_y * cos(-r);
		data->player.plane_x = old->plane_x * cos(-r)
			- data->player.plane_y * sin(-r);
		data->player.plane_y = old->plane_x * sin(-r)
			+ data->player.plane_y * cos(-r);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		data->player.dir_x = old->dir_x * cos(r) - data->player.dir_y * sin(r);
		data->player.dir_y = old->dir_x * sin(r) + data->player.dir_y * cos(r);
		old->plane_x = data->player.plane_x;
		data->player.plane_x = old->plane_x * cos(r)
			- data->player.plane_y * sin(r);
		data->player.plane_y = old->plane_x * sin(r)
			+ data->player.plane_y * cos(r);
	}
}

void	move_horizontally(t_game *game, double speed, t_data *data)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (data->map[(int)(data->player.y)]
			[(int)(data->player.x + data->player.dir_y * (speed + M))] != '1')
			data->player.x += data->player.dir_y * speed;
		if (data->map[(int)(data->player.y - data->player.dir_x * (speed + M))]
			[(int)(data->player.x)] != '1')
			data->player.y -= data->player.dir_x * speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (data->map[(int)(data->player.y)]
			[(int)(data->player.x - data->player.dir_y * (speed + M))] != '1')
			data->player.x -= data->player.dir_y * speed;
		if (data->map[(int)(data->player.y + data->player.dir_x * (speed + M))]
			[(int)(data->player.x)] != '1')
			data->player.y += data->player.dir_x * speed;
	}
}

void	move_player(t_game *game, t_data *data)
{
	double	speed;
	double	r;
	t_old	old;

	speed = (mlx_get_time() - game->last_time) * 3.0;
	game->last_time = mlx_get_time();
	old.dir_x = data->player.dir_x;
	old.plane_x = data->player.plane_x;
	r = speed * 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_vertically(game, speed, data);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		move_lr(game, &old, r, data);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_horizontally(game, speed, data);
}
