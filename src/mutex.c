/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:07:21 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 14:37:29 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex.h"
#include <pthread.h>
#include <stdlib.h>

t_mutex	new_mutex(void)
{
	t_mutex	mutex;

	mutex.pthread_mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex.pthread_mutex == NULL)
		return (mutex);
	if (pthread_mutex_init(mutex.pthread_mutex, NULL))
	{
		free(mutex.pthread_mutex);
		mutex.pthread_mutex = NULL;
	}
	return (mutex);
}

void	drop_mutex(t_mutex mutex)
{
	if (mutex.pthread_mutex)
	{
		pthread_mutex_destroy(mutex.pthread_mutex);
		free(mutex.pthread_mutex);
	}
}

void	mutex_destroy(t_mutex *self)
{
	if (self->pthread_mutex)
	{
		pthread_mutex_destroy(self->pthread_mutex);
		free(self->pthread_mutex);
		self->pthread_mutex = NULL;
	}
}

void	mutex_lock(t_mutex *self)
{
	if (self->pthread_mutex)
		pthread_mutex_lock(self);
}

void	mutex_unlock(t_mutex *self)
{
	if (self->pthread_mutex)
		pthread_mutex_unlock(self->pthread_mutex);
}
