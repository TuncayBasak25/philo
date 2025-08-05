/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:07:21 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 18:11:34 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex.h"
#include <pthread.h>
#include "mem.h"

t_mutex	new_mutex(void)
{
	t_mutex	mutex;

	mutex.pthread_mutex = mem_alloc(sizeof(pthread_mutex_t));
	if (mutex.pthread_mutex == NULL)
		return (mutex);
	if (pthread_mutex_init(mutex.pthread_mutex, NULL))
		mutex.pthread_mutex = mem_free(mutex.pthread_mutex);
	return (mutex);
}

void	drop_mutex(t_mutex mutex)
{
	if (mutex.pthread_mutex)
	{
		pthread_mutex_destroy(mutex.pthread_mutex);
		mem_free(mutex.pthread_mutex);
	}
}

void	mutex_destroy(t_mutex *self)
{
	if (self->pthread_mutex)
	{
		pthread_mutex_destroy(self->pthread_mutex);
		self->pthread_mutex = mem_free(self->pthread_mutex);
	}
}

void	mutex_lock(t_mutex *self)
{
	if (self->pthread_mutex)
		pthread_mutex_lock(self->pthread_mutex);
}

void	mutex_unlock(t_mutex *self)
{
	if (self->pthread_mutex)
		pthread_mutex_unlock(self->pthread_mutex);
}
