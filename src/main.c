
#include "../Include/cube.h"

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

	LOG_FUNC();
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
	return(0);
}
