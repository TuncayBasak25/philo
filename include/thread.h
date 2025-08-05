/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:48:27 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 14:31:17 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

typedef struct s_thread
{
	void	*pthread;
}	t_thread;


t_thread
new_thread(void *(*task)(void *), void *arg);

void
drop_thread(t_thread thread);

void
thread_destroy(t_thread *self);

void
thread_join(t_thread *self);

void
thread_detach(t_thread *self);

#endif