/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:53:30 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/10 11:04:28 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **argv)
{
	t_table	table;

	if (5 == ac || 6 == ac)
	{
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		error_exit("Wrong inputs. Check usage.");
}
