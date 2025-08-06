/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:18:58 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/06 22:38:04 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include "util.h"

typedef struct s_mutex
{
	t_bool	is_valid;
	t_u8	data[64];
}	t_mutex;

t_mutex
new_mutex(void);

void
drop_mutex(t_mutex mutex);

void
mutex_lock(t_mutex *self);

void
mutex_unlock(t_mutex *self);

#endif