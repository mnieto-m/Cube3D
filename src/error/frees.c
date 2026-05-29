/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:27:45 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 17:52:45 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

void	free_path(t_path *path)
{
	if (path->no)
		free(path->no);
	if (path->so)
		free(path->so);
	if (path->we)
		free(path->we);
	if (path->ea)
		free(path->ea);
	free(path);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->path)
		free_path(data->path);
	if (data->map)
		free_map(data->map);
	free(data);
}
