/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:19:53 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/03/27 17:14:35 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

int main(int argc, char **argv)
{
	t_data *data;
	
	if(argc != 2)
		print_error("Wrong numbers arguments");
	data = init_data(argv[1]);
	if(!data)
		print_error("Malloc error");
	parsing(data, argv[1]);
	return(0);
}