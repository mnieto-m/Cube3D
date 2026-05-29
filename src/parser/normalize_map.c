/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:29:00 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 17:57:52 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

static int	is_path_line(char *line)
{
	if (!line || !*line)
		return (1);
	while (*line == ' ' || *line == '\t')
		line++;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

void	normalize_map(t_data *data)
{
	int		i;
	int		j;
	int		count;
	size_t	len;
	char	**new_map;
	char	*new_line;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		if (!is_path_line(data->map[i]))
		{
			count++;
		}
		i++;
	}
	new_map = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_map)
		print_error("INVALID MAP: malloc error in normalize_map", data);
	i = 0;
	j = 0;
	while (data->map[i])
	{
		if (!is_path_line(data->map[i]))
		{
			len = ft_strlen(data->map[i]);
			new_line = (char *)malloc(data->max_len + 1);
			if (!new_line)
				print_error("INVALID MAP: malloc error in normalize_map", data);
			ft_memcpy(new_line, data->map[i], len);
			ft_memset(new_line + len, ' ', data->max_len - len);
			new_line[data->max_len] = '\0';
			new_map[j++] = new_line;
		}
		i++;
	}
	new_map[j] = NULL;
	free_map(data->map);
	data->map = new_map;
	data->max_h = j;
}
