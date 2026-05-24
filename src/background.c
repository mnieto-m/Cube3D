/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-24 15:36:40 by agnesgar          #+#    #+#             */
/*   Updated: 2026-05-24 15:36:40 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	draw_ceiling(t_ray *ray, t_game	*game, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_fast(game, x, y, game->path.ceiling_color);
		y++;
	}
}

void	draw_floor(t_ray *ray, t_game	*game, int x)
{
	int	y;

	y = ray->draw_end;
	while (y < HEIGHT)
	{
		put_pixel_fast(game, x, y, game->path.floor_color);
		y++;
	}
}
