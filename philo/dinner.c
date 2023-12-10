/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:43:01 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/10 11:33:41 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

static void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->nbr_threads_running);
	write_status(TAKE_FORK1, philo);
	while (!simulation_finished(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FORK1, philo);
	safe_mutex(&philo->second_fork->fork, LOCK);
	write_status(TAKE_FORK2, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meal_count++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meal_count == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
}

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->nbr_threads_running);
	desync_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->nbr_limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		safe_thread(&table->philos[0].thread_id, lone_philo,
			&table->philos[0], CREATE);
	else
		while (++i < table->philo_nbr)
			safe_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	safe_thread(&table->monitor, dinner_monitor, table, CREATE);
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread(&table->monitor, NULL, NULL, JOIN);
}
