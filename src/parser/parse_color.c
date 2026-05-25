#include "../Include/cube.h"

static void free_split(char **split)
{
	int i = 0;
	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void check_color_count(char **split, t_data *data)
{
    int count ;


	count = 0;
    while (split[count])
		count++;
	if (count != 3)
	{
		free_split(split);
		if (count < 3)
			print_error("INVALID MAP: missing color values (less than 3)", data);
		else
			print_error("INVALID MAP: too many color values (more than 3)", data);
	}
}
static int	ft_strisnum(const char *str)
{
	int i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isnum((unsigned char)str[i])&& str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int parsing_color(const char *line, t_data *data)
{
	char    **split;
	int     rgb[3];
	int     i;

	split = ft_split(line, ',');
	if (!split)
		print_error("INVALID MAP: malloc error", data);
	check_color_count(split, data);
	i = -1;
	while (++i < 3)
	{
		if (!split[i] || !ft_strisnum(split[i]))
		{
			free_split(split);
			print_error("INVALID MAP: color value is not numeric", data);
		}
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_split(split);
			print_error("INVALID MAP: color value out of range", data);
		}
	}
	free_split(split);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
