#include "../Include/cube.h"

void free_data(void *strtcutura)
{
	//LOG_FUNC();
	if(strtcutura)
		free(strtcutura);
}
