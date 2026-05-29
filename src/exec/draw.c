/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:37:23 by agnesgar          #+#    #+#             */
/*   Updated: 2026/05/29 17:30:11 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	put_pixel_fast(t_game *game, int x, int y, uint32_t color)
{
	uint8_t	*pixel;

	pixel = game->img->pixels + (y * WIDTH + x) * 4;
	pixel[0] = (color >> 24) & 0xFF;
	pixel[1] = (color >> 16) & 0xFF;
	pixel[2] = (color >> 8) & 0xFF;
	pixel[3] = color & 0xFF;
}

uint32_t	get_pixel_color(mlx_texture_t *texture, int index)
{
	return ((texture->pixels[index] << 24) | (texture->pixels[index
			+ 1] << 16) | (texture->pixels[index
			+ 2] << 8) | (texture->pixels[index + 3]));
}

uint32_t	apply_fog(double factor, uint32_t color)
{
	return ((((uint8_t)((color >> 24)
					* factor)) << 24) | (((uint8_t)(((color >> 16) & 0xFF)
					* factor)) << 16) | (((uint8_t)(((color >> 8) & 0xFF)
					* factor)) << 8) | (color & 0xFF));
}

void	draw_tex_strip(t_ray *ray, t_game *game, int x, mlx_texture_t *texture)
{
	int			tex_y;
	int			y;
	int			index;
	uint32_t	color;
	double		step;

	step = (double)texture->height / ray->line_height;
	game->tex_pos = (ray->draw_start - HEIGHT
			/ 2 + ray->line_height / 2) * step;
	if (game->tex_pos < 0)
		game->tex_pos = 0;
	y = ray->draw_start;
	game->factor = 1.0 / (1.0 + ray->wall_dist * 0.3);
	while (y <= ray->draw_end)
	{
		tex_y = (int)game->tex_pos;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		game->tex_pos += step;
		index = (tex_y * texture->width + ray->tex_x) * 4;
		color = get_pixel_color(texture, index);
		color = apply_fog(game->factor, color);
		put_pixel_fast(game, x, y, color);
		y++;
	}
}

void	paint_wall(t_ray *ray, t_game *game, int x)
{
	mlx_texture_t	*texture;

	texture = get_texture(ray, game);
	ray->tex_x = (int)(ray->wall_x * texture->width);
	if (ray->tex_x >= (int)texture->width)
		ray->tex_x = texture->width - 1;
	draw_tex_strip(ray, game, x, texture);
}
