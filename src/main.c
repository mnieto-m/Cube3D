/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:19:53 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/04/12 20:58:48 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

<<<<<<< HEAD
static char	r0[]  = "1111111111111111111111111";
static char	r1[]  = "1000000000110000000000001";
static char	r2[]  = "1011000001110000000000001";
static char	r3[]  = "1001000000000000000000001";
static char	r4[]  = "111111111011000001110000000000001";
static char	r5[]  = "100000000011000001110111111111111";
static char	r6[]  = "11110111111111011100000010001";
static char	r7[]  = "11110111111111011101010010001";
static char	r8[]  = "11000000110101011100000010001";
static char	r9[]  = "10000000000000001100000010001";
static char	r10[] = "10000000000000001101010010001";
static char	r11[] = "11000001110101011111011110N0111";
static char	r12[] = "11110111 1110101 101111010001";
static char	r13[] = "11111111 1111111 111111111111";

char		*g_map[] = {
	r0, r1, r2, r3, r4, r5, r6, r7,
	r8, r9, r10, r11, r12, r13, NULL
};

void	find_player(char **map, t_player *player) // norminetear
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				if (map[y][x] == 'N')
				{ player->dir_x = 0; player->dir_y = -1;
					player->plane_x = 0.66; player->plane_y = 0; }
				else if (map[y][x] == 'S')
				{ player->dir_x = 0; player->dir_y = 1;
					player->plane_x = -0.66; player->plane_y = 0; }
				else if (map[y][x] == 'E')
				{ player->dir_x = 1; player->dir_y = 0;
					player->plane_x = 0; player->plane_y = 0.66; }
				else
				{ player->dir_x = -1; player->dir_y = 0;
					player->plane_x = 0; player->plane_y = -0.66; }
				map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

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
	mlx_image_to_window(game->mlx, game->img_sprite, WIDTH - game->img_sprite->width, HEIGHT - game->img_sprite->height);
	mlx_delete_texture(tex);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: ./cub3D <map.cub>\n");
		return (1);
	}
	(void)argv;
	find_player(g_map, &game.player);
	game.map = g_map;
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_close_hook(game.mlx, close_hook, &game);
	game.tex_no = mlx_load_png("./textures/north1.png");
	game.tex_so = mlx_load_png("./textures/south1.png");
	game.tex_we = mlx_load_png("./textures/west1.png");
	game.tex_ea = mlx_load_png("./textures/east1.png");
	load_sprite(&game);
	game.path.ceiling_color = 0xACE5EEFF;
	game.path.floor_color = 0x7CB87FFF;
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	mlx_end(&game);
	return (0);
}
=======

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
>>>>>>> e481d69faaff7576d4d7b656662e16012c93ac2d
*/