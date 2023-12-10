/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:45:15 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/10 11:12:59 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if ((TAKE_FORK1 == status || TAKE_FORK2 == status)
		&& !simulation_finished(philo->table))
		printf(W "%-6ld" RST " %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(W "%-6ld" C " %d is eating\n" RST, elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(W "%-6ld" B " %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(W "%-6ld" M " %d is thinking\n" RST, elapsed, philo->id);
	else if (DIED == status)
		printf(R "%-6ld %d died\n" RST, elapsed, philo->id);
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}
