/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:42:04 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/05/29 17:44:16 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../Include/cube.h"

struct					s_data;
typedef struct s_data	t_data;

int						print_error(char *str, t_data *data);
void					free_data(t_data *data);
void					free_map(char **map);

#endif