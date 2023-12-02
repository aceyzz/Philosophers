/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:34:48 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/02 13:08:51 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Usage :	./philo <nb_de_philo> <die_time> <eat_time> <sleep_time> <[nb_repas]> */
/* ----------------------------------------------------- Librairies standards */
# include <unistd.h>	// write, usleep
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// mutex (init destroy lock unlock) & threads (create join detach)
# include <string.h>	// memset
# include <stdbool.h>	// true & false
# include <limits.h>	// INT_MAX, INT_MIN
# include <errno.h>		// handle errors

/* ---------------------------------------------------- Aliases (short names) */
typedef pthread_mutex_t	t_mtx; // ceci est un mutex

/* -------------------------------------------------------------------- enums */
typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_opcode;

typedef enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}				t_time_code;

typedef enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}				t_status;

/* ------------------------------------------------------------ Printf colors */
# define RST "\033[0m"
# define R "\033[1;31m"	// RED
# define G "\033[1;32m"	// GREEN
# define Y "\033[1;33m"	// YELLOW
# define B "\033[1;34m"	// BLUE
# define M "\033[1;35m"	// MAGENTA
# define C "\033[1;36m"	// CYAN
# define W "\033[1;37m"	// WHITE
/* -------------------------------------------------------------- Alias debug */
# define DEBUG_MODE 0
/* --------------------------------------------------------------- Structures */
typedef struct	s_table;
/*     Fourchettes    */
typedef struct	s_forks
{
	t_mtx		fork;
	int			fork_id;
}				t_forks;

/*     Philosophes    */
typedef struct	s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_forks		*first_fork;
	t_forks		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;

/*    Table de jeu    */
typedef struct	s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	bool		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_forks		*forks;		// tableau de forks
	t_philo		*philos;	// tableau de philosophes
}				t_table;

/* ---------------------------------------------------------------- Fonctions */
/*            utils.c            */
void	error_exit(const char *error);
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
/*            parse.c            */
void	parse_input(t_table *table, char *argv[]);
/*            safer.c            */
void	*safe_malloc(size_t bytes);
void	safe_mutex(t_mtx *mutex, t_opcode opcode);
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode);
/*             init.c            */
void	data_init(t_table *table);
/*            get_set.c          */
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_table *table);
/*          utils_sync.c         */
void	wait_all_threads(t_table *table);
/*            write.c            */
void	write_status(t_status status, t_philo *philo, bool debug);

#endif
