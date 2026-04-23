#include "../Include/cube.h"

// player position in parsin x and y

void player_str_pos(t_data *data, int y, int x)
{
	LOG_FUNC();
	if(data->player.start_x != -1 && data->player.start_y != -1)
		print_error("INVALID MAP", data);
	data->player.start_x = x;
	data->player.start_y = y;
}

int validate_map(t_data *data)
{
	int y;
	int x;

	LOG_FUNC();
	y = 0;
	while(y < data->max_h)
	{
		if(data->map[y][0] != '1' || data->map[y][data->max_len])
			print_error("INVALID MAP", data);
		
		if(y== 0 || y == data->max_h -1)
		{
			x = 0;
			while(x < data->max_len)
			{
				if(ft_strchr("N", data->map[y][x]))
					player_str_pos(data, y, x);
				if(ft_strchr("0NSEW", data->map[y][x]))
					print_error("INVALID MAP", data);
				x++;
			}
		}
		y++;
	}
	return(1);
}