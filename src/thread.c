/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:31:31 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 18:15:54 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"
#include "mem.h"
#include <pthread.h>

t_thread	new_thread(void *(*task)(void *), void *arg)
{
	t_thread	thread;

	if (!task)
	{
		thread.pthread = NULL;
		return (thread);
	}
	thread.pthread = mem_alloc(sizeof(pthread_t));
	if (thread.pthread == NULL)
		return (thread);
	if (pthread_create((pthread_t *)thread.pthread, NULL, task, arg))
		thread.pthread = mem_free(thread.pthread);
	return (thread);
}

void	drop_thread(t_thread thread)
{
	if (thread.pthread)
	{
		pthread_detach(*(pthread_t *)thread.pthread);
		mem_free(thread.pthread);
	}
}

void	thread_destroy(t_thread *self)
{
	if (self->pthread)
	{
		pthread_detach(*(pthread_t *)self->pthread);
		self->pthread = mem_free(self->pthread);
	}
}

void	thread_join(t_thread *self)
{
	if (self->pthread)
	{
		pthread_join(*(pthread_t *)self->pthread, NULL);
		self->pthread = mem_free(self->pthread);
	}
}

void	thread_detach(t_thread *self)
{
	thread_destroy(self);
}
