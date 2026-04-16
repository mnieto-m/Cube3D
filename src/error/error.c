#include "../Include/cube.h"



int print_error(char *str, t_data *data)
{
	printf("%s", str);
	free_main(data);
	exit(1);
}