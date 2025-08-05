/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:31:31 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 14:43:02 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "thread.h"

t_thread
new_thread(void *(*task)(void *), void *arg)
{
	t_thread	thread;

	if (!task)
	{
		thread.pthread = NULL;
		return (thread);
	}
	thread.pthread = malloc(sizeof(pthread_t));
	if (thread.pthread == NULL)
		return (thread);
	if (pthread_create(thread.pthread, NULL, task, arg))
	{
		free(thread.pthread);
		thread.pthread = NULL;
	}
	return (thread);
}

void
drop_thread(t_thread thread)
{
	if (thread.pthread)
	{
		pthread_detach(thread.pthread);
		free(thread.pthread);
	}
}

void
thread_destroy(t_thread *self)
{
	if (self->pthread)
	{
		pthread_detach(self->pthread);
		free(self->pthread);
		self->pthread = NULL;
	}
}

void
thread_join(t_thread *self)
{
	if (self->pthread)
	{
		pthread_join(self->pthread, NULL);
		free(self->pthread);
		self->pthread = NULL;
	}
}

void
thread_detach(t_thread *self)
{
	thread_destroy(self);
}
