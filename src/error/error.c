#include "../Include/cube.h"



int print_error(char *str, t_data *data)
{
	printf("%s\n", str);
	free_data(data);
	exit(1);
}