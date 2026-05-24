#include "../Include/cube.h"


static void many_colors (char **split, t_data *data)
{
	if (split[3])
	{
		//hay que agregar un bucle while para liberar los restantes 
		ft_mfree(4, split[0], split[1], split[2], split);
		print_error("Color: demasiados valores", data);
	}
}
int parsing_color(const char *line, t_data *data)
{
	char    **split;
	int     rgb[3];
	int     i;

	split = ft_split(line, ',');
	if (!split)
		print_error("Malloc error", data);
	i = 0;
	while (i < 3)
	{
		if (!split[i] || !ft_isnum(split[i]))
		{
			ft_mfree(4, split[0], split[1], split[2], split);
			print_error("Color: valor no numérico", data);
		}
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_mfree(4, split[0], split[1], split[2], split);
			print_error("Color: valor fuera de rango", data);
		}
		i++;
	}
	ft_mfree(4, split[0], split[1], split[2], split);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
