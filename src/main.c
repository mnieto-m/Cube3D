
#include "../Include/cube.h"

// Función para pintar un píxel en la imagen con color y opacidad
static void	paint_pixel(mlx_image_t *image, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t opacity)
{
	uint32_t	color;

	if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
	{
		color = (r << 24) | (g << 16) | (b << 8) | opacity;
		mlx_put_pixel(image, x, y, color);
	}
}

// Función para dibujar un cuadrado lleno (para el jugador en el minimap)
static void	draw_player(mlx_image_t *image, double center_x, double center_y, int size, uint8_t r, uint8_t g, uint8_t b)
{
	int	x;
	int	y;
	int	half_size;

	half_size = size / 2;
	y = (int)center_y - half_size;
	while (y < (int)center_y + half_size)
	{
		x = (int)center_x - half_size;
		while (x < (int)center_x + half_size)
		{
			paint_pixel(image, x, y, r, g, b, 255);
			x++;
		}
		y++;
	}
}

// Función para pintar un rectángulo (celda del mapa)
static void	paint_cell(mlx_image_t *image, int start_x, int start_y, int size, uint8_t opacity)
{
	int	x;
	int	y;

	y = start_y;
	while (y < start_y + size)
	{
		x = start_x;
		while (x < start_x + size)
		{	
			paint_pixel(image, x, y, MINIMAP_WALL_RGB, opacity);
			x++;
		}
		y++;
	}
}

// Función para renderizar solo el mapa estático en la imagen
static void	render_minimap_static(mlx_image_t *image, t_data *data, int scale)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->max_h && y * scale < (int)image->height)
	{
		x = 0;
		while (data->map[y] && x < (int)ft_strlen(data->map[y]) && x * scale < (int)image->width)
		{
			if (data->map[y][x] == '1')
				paint_cell(image, x * scale, y * scale, scale, MINIMAP_WALL_OPAQUE);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'N' 
				|| data->map[y][x] == 'S' || data->map[y][x] == 'E' 
				|| data->map[y][x] == 'W')
				paint_cell(image, x * scale, y * scale, scale, MINIMAP_FLOOR_TRANSPARENT);
			x++;
		}
		y++;
	}
}


static int	validate_name(const char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

int main(int argc, char **argv)
{
	t_data *data;

	//LOG_FUNC();
	data = NULL;
	
	if(argc != 2)
		print_error("INVALID MAP: wrong number of arguments",data);
	if (!validate_name(argv[1]))
		print_error("INVALID MAP: file extension must be .cub", data);
	data = init_data(argv[1]);
	if(!data)
		print_error("INVALID MAP: malloc error",data);
	data->map = read_map(argv[1], data);
	parse(data);
	printf("llegue al final");
	
	#define WIDTH 3840	
	#define HEIGHT 2160

	mlx_t *mlx;
	mlx_image_t *minimap_static;	// Imagen estática del mapa
	mlx_image_t *player_image;		// Imagen dinámica del jugador
	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	// Crear imagen estática del mapa con tamaño suficiente para el minimap escalado
	int minimap_width = data->max_len * MINIMAP_SCALE;
	int minimap_height = data->max_h * MINIMAP_SCALE;
	
	if (!(minimap_static = mlx_new_image(mlx, minimap_width, minimap_height)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	// Crear imagen dinámica del jugador (mismo tamaño que el mapa)
	if (!(player_image = mlx_new_image(mlx, minimap_width, minimap_height)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	// Renderizar el mapa estático UNA SOLA VEZ
	render_minimap_static(minimap_static, data, MINIMAP_SCALE);
	
	// Dibujar la posición inicial del jugador
	double player_render_x = (double)data->player.start_x * MINIMAP_SCALE;
	double player_render_y = (double)data->player.start_y * MINIMAP_SCALE;
	draw_player(player_image, player_render_x, player_render_y, PLAYER_SIZE, PLAYER_COLOR_RGB);
	
	if (mlx_image_to_window(mlx, minimap_static, 10, 10) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	if (mlx_image_to_window(mlx, player_image, 10, 10) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
	return(0);
}
