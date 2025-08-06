/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:28:30 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/07 00:09:29 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sync_bool.h"

t_sync_bool	new_sync_bool(t_bool initial_state)
{
	t_sync_bool	sbool;

	sbool.mutex = new_mutex();
	sbool.state = initial_state;
	return (sbool);
}

void	drop_sync_bool(t_sync_bool sbool)
{
	drop_mutex(sbool.mutex);
}

t_bool	sync_bool_get(t_sync_bool *self)
{
	t_bool	res;

	if (self)
	{
		mutex_lock(&self->mutex);
		res = self->state;
		mutex_unlock(&self->mutex);
	}
	else
		res = FALSE;
	return (res);
}

void	sync_bool_set(t_sync_bool *self, t_bool new_state)
{
	if (self)
	{
		mutex_lock(&self->mutex);
		self->state = new_state;
		mutex_unlock(&self->mutex);
	}
}

t_result
	sync_bool_cas(t_sync_bool *self, t_bool expected_state, t_bool new_state)
{
	t_result	res;

	if (self)
	{
		mutex_lock(&self->mutex);
		if (self->state == expected_state)
		{
			self->state = new_state;
			res = OK;
		}
		else
			res = FAIL;
		mutex_unlock(&self->mutex);
	}
	else
		res = FAIL;
	return (res);
}
