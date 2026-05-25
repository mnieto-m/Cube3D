#include "../Include/cube.h"

void	print_tdata(char *str, t_data *data)
{
    int	i;

    puts(str);
    if (data->path)
    {
        ft_printf("NO: %s\n", data->path->no);
        ft_printf("SO: %s\n", data->path->so);
        ft_printf("WE: %s\n", data->path->we);
        ft_printf("EA: %s\n", data->path->ea);
        ft_printf("Floor color: %d\n", data->path->floor_color);
        ft_printf("Ceiling color: %d\n", data->path->ceiling_color);
    }
    else
        ft_printf("Sin path\n");
    ft_printf("max_len: %d\n", data->max_len);
    ft_printf("max_h: %d\n", data->max_h);
    ft_printf("Player start: x=%d, y=%d\n", data->player.start_x, data->player.start_y);
    ft_printf("Mapa:\n");
    i = 0;
    if (data->map)
    {
        while (data->map[i])
        {
            ft_printf("[%d]: %s\n", i, data->map[i]);
            i++;
        }
    }
    else
        ft_printf("Sin mapa\n");
    ft_printf("----- fin t_data -----\n");
}


void	parse(t_data *data)
{
	parse_textures(data, data->map);
    normalize_map(data);
    validate_map(data);
}
