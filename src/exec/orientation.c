/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-23 20:06:49 by agnesgar          #+#    #+#             */
/*   Updated: 2026-05-23 20:06:49 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

mlx_texture_t	*get_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0 && ray->step_x == 1)
		return (game->tex_ea);
	if (ray->side == 0 && ray->step_x == -1)
		return (game->tex_we);
	if (ray->side == 1 && ray->step_y == 1)
		return (game->tex_so);
	return (game->tex_no);
}
