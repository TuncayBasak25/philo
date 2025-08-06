/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:07:21 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/06 22:32:15 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex.h"
#include <pthread.h>

t_mutex	new_mutex(void)
{
	t_mutex	mutex;

	if (pthread_mutex_init((pthread_mutex_t *)&mutex.data, NULL))
		mutex.is_valid = FALSE;
	else
		mutex.is_valid = TRUE;
	return (mutex);
}

void	drop_mutex(t_mutex mutex)
{
	if (mutex.is_valid)
		pthread_mutex_destroy((pthread_mutex_t *)&mutex.data);
}

void	mutex_lock(t_mutex *self)
{
	if (self && self->is_valid)
		pthread_mutex_lock((pthread_mutex_t *)&self->data);
}

void	mutex_unlock(t_mutex *self)
{
	if (self && self->is_valid)
		pthread_mutex_unlock((pthread_mutex_t *)&self->data);
}
