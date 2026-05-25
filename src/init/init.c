#include "../Include/cube.h"


int correct_format(char *str)
{
	int len;

	LOG_FUNC();
	len = ft_strlen(str);
	if (len >= 4 && ft_strncmp(str + len - 4, ".cub", 4) == 0)
		return(1);
	return(0);
}

t_data *init_data(char *src)
{
	t_data *data;

	LOG_FUNC();
	data = NULL;

	if(!correct_format(src))
		print_error("INVALID MAP: file extension must be .cub", data);
	data = malloc(sizeof(t_data));
	if(!data)
		print_error("INVALID MAP: malloc error", data);
	data->path = ft_calloc(1, sizeof(t_path));
	data->path->ceiling_color = -1;
	data->path->floor_color = -1;
	data->map = NULL;
	data->max_len = 0;
	data->max_h = 0;
	data->player.start_x = -1;
	data->player.start_y = -1;
	return(data);
}
