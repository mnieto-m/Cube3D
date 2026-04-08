#include "../Include/cube.h"


int correct_format(char *str)
{
	int len = ft_strlen(str);
	if(ft_strnstr(str,".cub", len) && str[len + 1] == '\0')
		return(1);
	return(0);
}

t_data *init_data(char *src)
{
	t_data *data;

	if(correct_format(src))
		print_error("bad format map etc");
	data = malloc(sizeof(t_data));
	if(!data)
		print_error("Malloc error");
	data->path = NULL;
	data->map = NULL;
	data->max_len = 0;
	return(data);
}