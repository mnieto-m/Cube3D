/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-18 11:42:25 by agnesgar          #+#    #+#             */
/*   Updated: 2026-05-18 11:42:25 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

#define MARGIN 0.5

void	move_vertically(t_game *game, double speed)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (game->map[(int)(game->player.y)]
			[(int)(game->player.x + game->player.dir_x * (speed + MARGIN))] != '1')
			game->player.x += game->player.dir_x * speed;
		if (game->map[(int)(game->player.y + game->player.dir_y * (speed + MARGIN))]
			[(int)(game->player.x)] != '1')
			game->player.y += game->player.dir_y * speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (game->map[(int)(game->player.y)]
			[(int)(game->player.x - game->player.dir_x * (speed + MARGIN))] != '1')
			game->player.x -= game->player.dir_x * speed;
		if (game->map[(int)(game->player.y - game->player.dir_y * (speed + MARGIN))]
			[(int)(game->player.x)] != '1')
			game->player.y -= game->player.dir_y * speed;
	}
}

void	move_left_or_right(t_game *game, double olddir_x, double oldplane_x, double rot)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.dir_x = olddir_x * cos(-rot) - game->player.dir_y * sin(-rot);
		game->player.dir_y = olddir_x * sin(-rot) + game->player.dir_y * cos(-rot);
		game->player.plane_x = oldplane_x * cos(-rot)
			- game->player.plane_y * sin(-rot);
		game->player.plane_y = oldplane_x * sin(-rot)
			+ game->player.plane_y * cos(-rot);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.dir_x = olddir_x * cos(rot) - game->player.dir_y * sin(rot);
		game->player.dir_y = olddir_x * sin(rot) + game->player.dir_y * cos(rot);
		oldplane_x = game->player.plane_x;
		game->player.plane_x = oldplane_x * cos(rot)
			- game->player.plane_y * sin(rot);
		game->player.plane_y = oldplane_x * sin(rot)
			+ game->player.plane_y * cos(rot);
	}
}

void	move_horizontally(t_game *game, double speed)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (game->map[(int)(game->player.y)]
			[(int)(game->player.x + game->player.dir_y * (speed + MARGIN))] != '1')
			game->player.x += game->player.dir_y * speed;
		if (game->map[(int)(game->player.y - game->player.dir_x * (speed + MARGIN))]
			[(int)(game->player.x)] != '1')
			game->player.y -= game->player.dir_x * speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (game->map[(int)(game->player.y)]
			[(int)(game->player.x - game->player.dir_y * (speed + MARGIN))] != '1')
			game->player.x -= game->player.dir_y * speed;
		if (game->map[(int)(game->player.y + game->player.dir_x * (speed + MARGIN))]
			[(int)(game->player.x)] != '1')
			game->player.y += game->player.dir_x * speed;
	}
}

void	move_player(t_game *game)
{
	double	speed;
	double	olddir_x;
	double	oldplane_x;
	double	rot;

	speed = (mlx_get_time() - game->last_time) * 3.0;
	game->last_time = mlx_get_time();
	olddir_x = game->player.dir_x;
	oldplane_x = game->player.plane_x;
	rot = speed * 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_vertically(game, speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		move_left_or_right(game, olddir_x, oldplane_x, rot);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_horizontally(game, speed);
}
