/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:19:53 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 17:31:49 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	mlx_end(t_game *game)
{
	mlx_delete_texture(game->tex_no);
	mlx_delete_texture(game->tex_ea);
	mlx_delete_texture(game->tex_we);
	mlx_delete_texture(game->tex_so);
	mlx_delete_image(game->mlx, game->img_sprite);
	mlx_terminate(game->mlx);
}

static void	find_player2(t_data *data)
{
	if (data->player.orientation == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (data->player.orientation == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

static void	find_player(t_data *data)
{
	data->player.x = data->player.start_x + 0.5;
	data->player.y = data->player.start_y + 0.5;
	if (data->player.orientation == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.orientation == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	find_player2(data);
}

static void	load_sprite(t_game *game)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("./textures/sprite.png");
	game->img_sprite = mlx_texture_to_image(game->mlx, tex);
	mlx_image_to_window(game->mlx, game->img_sprite,
		WIDTH - game->img_sprite->width, HEIGHT - game->img_sprite->height);
	mlx_delete_texture(tex);
}

int	exec(t_data *data)
{
	t_game	game;

	game.data = data;
	find_player(data);
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_close_hook(game.mlx, close_hook, &game);
	game.tex_no = mlx_load_png("./textures/north1.png");
	game.tex_so = mlx_load_png("./textures/south1.png");
	game.tex_we = mlx_load_png("./textures/west1.png");
	game.tex_ea = mlx_load_png("./textures/east1.png");
	load_sprite(&game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	mlx_end(&game);
	return (0);
}
