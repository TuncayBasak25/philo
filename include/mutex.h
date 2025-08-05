/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:48:27 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 13:25:08 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

typedef struct s_mutex
{
	void	*pthread_mutex;
}	t_mutex;

t_mutex
new_mutex(void);

void
drop_mutex(t_mutex mutex);

void
mutex_destroy(t_mutex *self);

void
mutex_lock(t_mutex *self);

void
mutex_unlock(t_mutex *self);

#endif