#include "../Include/cube.h"



void player_str_pos(t_data *data, int y, int x)
{
	LOG_FUNC();
	if(data->player.start_x  == -1 && data->player.start_y  == -1)
	{
		data->player.start_x = x;
		data->player.start_y = y;
	}
	else if (data->player.start_x != -1 && data->player.start_y != -1)
		print_error("INVALID MAP: DUPLICATE PLAYER", data);
}

int valided_player(t_data *data)
{
	printf("%i\n", data->player.start_x);
	printf("%i\n", data->player.start_y);
	if(data->player.start_x == -1 && data->player.start_y  == -1)
		print_error("INVALID MAP: NO PLAYER", data);
	return(0);
}

int validate_map(t_data *data)
{
	int y;
	int x;
	int last;

	y = 0;
	while (y < data->max_h)
	{
		last = data->max_len - 1;
		while (last >= 0 && data->map[y][last] == ' ')
			last--;
		x = 0;
		while (x < data->max_len)
		{
			if (!ft_strchr("01NSEW ", data->map[y][x]))
				print_error("INVALID MAP: invalid character", data);
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				if (y == 0 || y == data->max_h - 1 || x == 0 || x == last)
					print_error("INVALID MAP: player on edge", data);
				player_str_pos(data, y, x);
			}
			if ((y == 0 || y == data->max_h - 1 || x == 0 || x == last) && data->map[y][x]== '0')
				print_error("INVALID MAP: open border", data);
			x++;
		}
		y++;
	}
	valided_player(data);
	return (1);
}
