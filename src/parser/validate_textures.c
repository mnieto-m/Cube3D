/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 18:18:57 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 21:58:37 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

static int	is_valid_png_file(const char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".png", 4) == 0);
}

int	validate_textures(t_data *data)
{
	if (!data->path->no)
		print_error("INVALID MAP: missing NO texture", data);
	else if (!is_valid_png_file(data->path->no))
		print_error("INVALID MAP: NO must be .png file", data);
	if (!data->path->so)
		print_error("INVALID MAP: missing SO texture", data);
	else if (!is_valid_png_file(data->path->so))
		print_error("INVALID MAP: SO must be .png file", data);
	if (!data->path->we)
		print_error("INVALID MAP: missing WE texture", data);
	else if (!is_valid_png_file(data->path->we))
		print_error("INVALID MAP: WE must be .png file", data);
	if (!data->path->ea)
		print_error("INVALID MAP: missing EA texture", data);
	else if (!is_valid_png_file(data->path->ea))
		print_error("INVALID MAP: EA must be .png file", data);
	if (data->path->floor_color == -1)
		print_error("INVALID MAP: missing floor color", data);
	if (data->path->ceiling_color == -1)
		print_error("INVALID MAP: missing ceiling color", data);
	return (1);
}
