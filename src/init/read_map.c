/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 18:17:28 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 18:28:52 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

// static void	log_map_content(char **lines)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("[LOG] map content start\n");
// 	while (lines && lines[i])
// 	{
// 		ft_printf("[LOG] map[%d]: %s\n", i, lines[i]);
// 		i++;
// 	}
// 	ft_printf("[LOG] map content end\n");
// }

static char	*read_file_to_buffer(int fd, t_data *data)
{
	char	*buffer;
	char	*line;
	char	*tmp;

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
			print_error("INVALID MAP: malloc error", data);
		}
		line = get_next_line(fd);
	}
	return (buffer);
}

char	**read_map(char *map, t_data *data)
{
	int		fd;
	char	**lines;
	char	*buffer;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		print_error("INVALID MAP: could not open file", data);
	buffer = read_file_to_buffer(fd, data);
	close(fd);
	if (!buffer || !*buffer)
		print_error("INVALID MAP: file is empty", data);
	lines = ft_split(buffer, '\n');
	if (!lines)
		print_error("INVALID MAP: split error", data);
	free(buffer);
	return (lines);
}
