/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:06:53 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/10 11:07:05 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("No negative values possible.");
	if (!is_digit(*str))
		error_exit("The input is not correct digit(s)");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("The value is too big. Maximum: INT_MAX");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("The value is too big. Maximum: INT_MAX");
	return (num);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr > PHILO_MAX)
		exit(EXIT_FAILURE);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_sleep < 6e4
		|| table->time_to_eat < 6e4)
		error_exit("Minimum timestamps: 60ms.");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}
