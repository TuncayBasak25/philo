/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:31:31 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/07 00:56:30 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"
#include <pthread.h>

t_thread	new_thread(t_fn_task task, void *arg)
{
	t_thread	thread;

	if (!task || pthread_create((pthread_t *)&thread.data, NULL, task, arg))
		thread.is_valid = FALSE;
	else
		thread.is_valid = TRUE;
	return (thread);
}

void	thread_join(t_thread *self)
{
	if (self && self->is_valid)
	{
		pthread_join(*(pthread_t *)&self->data, NULL);
		*self = (t_thread){0};
	}
}
