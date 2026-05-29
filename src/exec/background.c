/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 15:36:40 by agnesgar          #+#    #+#             */
/*   Updated: 2026/05/29 17:29:19 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	draw_ceiling(t_ray *ray, t_game *game, int x, t_data *data)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_fast(game, x, y, data->path->ceiling_color);
		y++;
	}
}

void	draw_floor(t_ray *ray, t_game *game, int x, t_data *data)
{
	int	y;

	y = ray->draw_end;
	while (y < HEIGHT)
	{
		put_pixel_fast(game, x, y, data->path->floor_color);
		y++;
	}
}
