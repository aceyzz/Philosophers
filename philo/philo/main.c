/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:53:30 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/02 12:32:18 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;
	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv); // √
		data_init(&table); // √
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_exit("Wrong input: "
				G"Correct is ./philo 5 800 200 200 [5]" RST);
	}
}
