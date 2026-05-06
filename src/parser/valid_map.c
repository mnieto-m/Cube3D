#include "../Include/cube.h"

// player position in parsin x and y
// problema si no consigo donde esta data- max.h 

void player_str_pos(t_data *data, int y, int x)
{
	LOG_FUNC();
	if(data->player.start_x  == -1 && data->player.start_y  == -1)
	{
		data->player.start_x = x;
		data->player.start_y = y;
	}
	else if (data->player.start_x != -1 && data->player.start_y != -1)
		print_error("DOBLE PLAYER", data);
}

int valided_player(t_data *data)
{
	printf("%i\n", data->player.start_x);
	printf("%i\n", data->player.start_y);
	if(data->player.start_x == -1 && data->player.start_y  == -1)
		print_error("NO PLAYER", data);
	return(0);
}

int validate_map(t_data *data)
{
	int y;
	int x;
	printf("%i\n", data->max_h);
	printf("%i\n", data->max_len);
y = 0;
while (y < data->max_h)
{
    x = 0;
            while (x < data->max_len)
            {

				if (!ft_strchr("01NSEW ", data->map[y][x]))
					print_error("INVALID MAP: caracter invalido", data);
				if (ft_strchr("NSEW", data->map[y][x]))
				{
					if (y == 0 || y == data->max_h - 1 || x == 0 || x == data->max_len - 1)
						print_error("INVALID MAP: jugador en borde", data);
					player_str_pos(data, y, x);
				}
				if ((y == 0 || y == data->max_h - 1 || x == 0 || x == data->max_len - 1)
					&& data->map[y][x] != '1' && data->map[y][x] != ' ')
					print_error("INVALID MAP: borde no cerrado", data);

                x++;
            }
    y++;
}
valided_player(data);
return 1;
}
