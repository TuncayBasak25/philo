/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_bool.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:18:58 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/06 22:32:32 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNC_BOOL_H
# define SYNC_BOOL_H

# include "mutex.h"

typedef struct s_sync_bool
{
	t_mutex	mutex;
	t_bool	state;
}	t_sync_bool;

t_sync_bool
new_sync_bool(t_bool initial_state);

void
drop_sync_bool(t_sync_bool sbool);

t_bool
sync_bool_get(t_sync_bool *self);

void
sync_bool_set(t_sync_bool *self, t_bool new_state);

t_result
sync_bool_cas(t_sync_bool *self, t_bool expected_state, t_bool new_state);

#endif