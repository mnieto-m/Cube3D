#include "../Include/cube.h"



int print_error(char *str, t_data *data)
{
	//LOG_FUNC();
	printf("%s\n", str);
	(void)(data);
	//free_data(data);
	exit(1);
}