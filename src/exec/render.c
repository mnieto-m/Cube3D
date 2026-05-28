/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:45:33 by agnesgar          #+#    #+#             */
/*   Updated: 2026/05/25 21:43:49 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	perpendicular_ray(t_ray	*ray, t_data *data)
{
	// distancia perpendicular si chocó en y o en x

	if (ray->side == 0)
	{
		ray->wall_dist = ray->sidedist_x - ray->deltadist_x;
	}
	else if (ray->side == 1)
	{
		ray->wall_dist = ray->sidedist_y - ray->deltadist_y;
	}
	ray->line_height = HEIGHT / ray->wall_dist;
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0) // este u oeste, el rayo viene de los lados, importa posicion Y
		ray->wall_x = data->player.y + ray->wall_dist * ray->dir_y;
	else if (ray->side == 1) // norte o sur, rayo desde arriba o abajo, importa posicion X
		ray->wall_x = data->player.x + ray->wall_dist * ray->dir_x;
	ray->wall_x = ray->wall_x - floor(ray->wall_x); // solo nos quedamos con la parte decimal
}

void	encounter_wall(t_ray *ray, t_game *game, int x, t_data *data)
{
	int	hit;

	hit = 0;

	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y) // dda
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else // si la linea "y" es mas cercana
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;			
		}
		if ((data->map[ray->map_y][ray->map_x]) == '1')
			hit = 1;
	}
	perpendicular_ray(ray, data);
	draw_ceiling(ray, game, x, data);
	draw_floor(ray, game, x, data);
	paint_wall(ray, game, x);
}

void	init_ray(t_ray *ray, t_data *data)
{
	ray->map_x = (int)data->player.x; // truncar decimal con (int) para saber celda
	ray->map_y = (int)data->player.y;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->player.x - ray->map_x) * ray->deltadist_x;
	}
	else if (ray->dir_x > 0)
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - data->player.x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->player.y - ray->map_y) * ray->deltadist_y;
	}
	else if (ray->dir_y > 0)
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - data->player.y) * ray->deltadist_y;
	}
}

void	render(void *param)
{
	t_game	*game;
	t_ray	ray;
	int		x;
	double	cam_x;

	game = param;
	x = 0;
	move_player(game, game->data);
	while (x < WIDTH)
	{  // posición del jugador en x, +1, 0 o -1 respecto al centro.
		cam_x = 2.0 * x / WIDTH - 1.0;
		ray.dir_x = game->data->player.dir_x + game->data->player.plane_x * cam_x;
		ray.dir_y = game->data->player.dir_y + game->data->player.plane_y * cam_x;
		if (ray.dir_x == 0)
			ray.deltadist_x = 1e50; // numero infinito por si es 0.0, el rayo nunca cruza una linea vertical
		else // si va perfectamente en Y
			ray.deltadist_x = fabs(1.0 / ray.dir_x); // valor absoluto de un double
		if (ray.dir_y == 0)
			ray.deltadist_y = 1e50;
		else
			ray.deltadist_y = fabs(1.0 / ray.dir_y);
		init_ray(&ray, game->data);
		encounter_wall(&ray, game, x, game->data);
		x++;
	}
}
