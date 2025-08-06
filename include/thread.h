/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:18:58 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/06 22:34:23 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "util.h"

typedef struct s_thread
{
	t_bool	is_valid;
	t_u8	data[16];
}	t_thread;

typedef void	*(*t_fn_task)(void *);

t_thread
new_thread(t_fn_task task, void *arg);

void
thread_join(t_thread *self);

#endif