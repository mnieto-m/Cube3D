#ifndef ERROR_H
#define ERROR_H

#include "../Include/cube.h"

struct s_data;
typedef struct s_data t_data;

int print_error(char *str, t_data *data);
void free_data(void *strtcutura);

#endif