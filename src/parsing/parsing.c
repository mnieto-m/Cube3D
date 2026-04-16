#include "../Include/cube.h"


static char *read_file_to_buffer(int fd, t_data *data)
{
	char *buffer ;
	char *line;
    char *tmp;

    buffer = NULL;
    line = get_next_line(fd);
	while (line)
	{
		if (data->max_len < ft_strlen(line))
			data->max_len = ft_strlen(line);
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

	fd = open(map, O_RDONLY);
	if (fd < 0)
		print_error("No se pudo abrir el archivo", data);
	buffer = read_file_to_buffer(fd, data);
	close(fd);
	lines = ft_split(buffer, '\n');
	if (!lines)
		print_error("Split error", data);
	free(buffer);
	return (lines);
}
void	parsing(t_data *data, char *map)
{
	int	i;
    data->map = read_map(map, data);
	parsing_textures(data);
    //valid map
    normalize_map(data);
}
