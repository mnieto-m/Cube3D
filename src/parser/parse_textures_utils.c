/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:39:29 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 17:57:02 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

 void	skip_word(const char *line, int *i)
{
	while (line[*i] && !ft_isspace(line[*i]))
		(*i)++;
}
