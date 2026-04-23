/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:19:53 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/04/22 20:43:21 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

int main(int argc, char **argv)
{
	t_data *data;

	LOG_FUNC();
	data = NULL;
	
	if(argc != 2)
		print_error("Wrong numbers arguments",data);
	data = init_data(argv[1]);
	if(!data)
		print_error("Malloc error",data);
	parse(data, argv[1]);
	return(0);
}