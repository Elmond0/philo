/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:10:27 by elmondo           #+#    #+#             */
/*   Updated: 2026/01/14 13:10:25 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		return (NULL);
	return (ret);
}

static int	handle_thread_error(int status)
{
	if (0 == status)
		return (0);
	return (1);
}

int	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
	void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		return (handle_thread_error(pthread_create(thread, NULL, foo, data)));
	else if (JOIN == opcode)
		return (handle_thread_error(pthread_join(*thread, NULL)));
	else if (DETACH == opcode)
		return (handle_thread_error(pthread_detach(*thread)));
	return (1);
}

int	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		return (pthread_mutex_lock(mutex));
	else if (UNLOCK == opcode)
		return (pthread_mutex_unlock(mutex));
	else if (INIT == opcode)
		return (pthread_mutex_init(mutex, NULL));
	else if (DESTROY == opcode)
		return (pthread_mutex_destroy(mutex));
	return (1);
}
