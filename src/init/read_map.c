#include "../Include/cube.h"


static void	log_map_content(char **lines)
{
	int	i;

	i = 0;
	ft_printf("[LOG] map content start\n");
	while (lines && lines[i])
	{
		ft_printf("[LOG] map[%d]: %s\n", i, lines[i]);
		i++;
	}
	ft_printf("[LOG] map content end\n");
}

static char *read_file_to_buffer(int fd, t_data *data)
{
	char *buffer ;
	char *line;
    char *tmp;

	//LOG_FUNC();
    buffer = NULL;
    line = get_next_line(fd);
	while (line)
	{
		if (data->max_len < (int)ft_strlen(line))
			data->max_len = ft_strlen(line);
		data->max_h++;
		tmp = buffer;
		buffer = ft_strjoin(buffer, line);
		free(tmp);
		free(line);
		if (!buffer)
		{
			close(fd);
			print_error("Malloc error", data);
		}
		line = get_next_line(fd);
	}
	return (buffer);
}

char	**read_map(char *map, t_data *data)
{
	int		fd;
	char		**lines;
	char        *buffer;

	//LOG_FUNC();
	fd = open(map, O_RDONLY);
	if (fd < 0)
		print_error("No se pudo abrir el archivo", data);
	buffer = read_file_to_buffer(fd, data);
	close(fd);
	
	if (!buffer || !*buffer)
		print_error("INVALID MAP: File is empty", data);
	
	lines = ft_split(buffer, '\n');
	if (!lines)
		print_error("Split error", data);
	log_map_content(lines);
	free(buffer);
	return (lines);
}
