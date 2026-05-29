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

/*
int main(int argc, char **argv)
{
	t_data *data;
	
	if(argc != 2)
		print_error("Wrong numbers arguments",data);
	data = init_data(argv[1]);
	if(!data)
		print_error("Malloc error",data);
	parsing(data, argv[1]);
	return(0);
}
*/