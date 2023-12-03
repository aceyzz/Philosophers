/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:33:37 by cedmulle          #+#    #+#             */
/*   Updated: 2023/12/02 12:32:50 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid (default).");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid (default).");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if thread blocked waiting"
			"for mutex (default).");
	else if (status == EPERM)
		error_exit("The current thread dosn't hold a lock on mutex"
			"(default).");
	else if (status == ENOMEM)
		error_exit("The process can't allocate enough memomry to create"
			"another mutex (default).");
	else if (status == EBUSY)
		error_exit("Mutex is locked (default).");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No ressources to create another thread (default).");
	else if (status == EPERM)
		error_exit("The caller doesn't have right permissions (default).");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid (default).");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable"
			"(default).");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that"
			" specified by the fiven thread ID, thread (default).");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of thread specifies"
			"the calling thread (default).");
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret = NULL)
		error_exit("Malloc error.");
	return (ret);
}

void	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex.");
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle: "
			"use <CREATE> <JOIN> <DETACH>.");
}
