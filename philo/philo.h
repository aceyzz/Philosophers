/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:34:48 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/10 11:43:46 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* -------------------------------------------------------------------------- */
/*                          Libraires standards                               */
/* -------------------------------------------------------------------------- */
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/* -------------------------------------------------------------------------- */
/*                           Nombre max de philos                             */
/* -------------------------------------------------------------------------- */
# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

/* -------------------------------------------------------------------------- */
/*                                   Couleurs                                 */
/* -------------------------------------------------------------------------- */
# define RST	"\033[0m"
# define R		"\033[1;31m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define B		"\033[1;34m"
# define M      "\033[1;35m"
# define C      "\033[1;36m"
# define W      "\033[1;37m"

/* -------------------------------------------------------------------------- */
/*                                    Enums                                   */
/* -------------------------------------------------------------------------- */
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FORK1,
	TAKE_FORK2,
	DIED,
}			t_philo_status;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

/* -------------------------------------------------------------------------- */
/*                                  Structures                                */
/* -------------------------------------------------------------------------- */
typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

struct s_fork
{
	t_mtx		fork;
	int			fork_id;
};

struct s_philo
{
	int			id;
	bool		full;
	long		meal_count;
	long		last_meal_time;
	pthread_t	thread_id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mtx		philo_mutex;
	t_table		*table;
};

struct	s_table
{
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		philo_nbr;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		nbr_threads_running;
	pthread_t	monitor;
	t_fork		*forks;
	t_philo		*philos;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
};

/* -------------------------------------------------------------------------- */
/*                                Fonctions                                   */
/* -------------------------------------------------------------------------- */
/* dinner.c		*/
void	thinking(t_philo *philo, bool pre_simulation);
void	dinner_start(t_table *table);
/* get_set.c	*/
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);
/* init.c		*/
void	data_init(t_table *table);
/* monitor.c	*/
void	*dinner_monitor(void *data);
/* parse.c		*/
void	parse_input(t_table *table, char **argv);
/* safer.c		*/
void	safe_mutex(t_mtx *mutex, t_opcode opcode);
void	*safe_malloc(size_t bytes);
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
/* utils_sync.c	*/
void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	desync_philos(t_philo *philo);
/* utils.c		*/
time_t	gettime(int time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
void	error_exit(const char *error);
/* write.c		*/
void	write_status(t_philo_status status, t_philo *philo);

#endif
