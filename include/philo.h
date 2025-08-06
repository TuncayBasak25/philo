/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:48:27 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/06 23:40:14 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "sync_bool.h"
# include "thread.h"

typedef struct s_philo
{
	t_usize		id;
	t_usize		eat_count;
	t_usize		start_time;
	t_usize		last_meal;
	t_usize		tt_die;
	t_usize		tt_sleep;
	t_usize		tt_eat;
	t_usize		eat_max;
	t_sync_bool	*left;
	t_sync_bool	*right;
	t_sync_bool	*running;
	t_mutex		*log_mutex;
	t_thread	thread;
}	t_philo;

typedef enum e_philo_action
{
	PHILO_DIE,
	PHILO_FORK,
	PHILO_EAT,
	PHILO_SLEEP,
	PHILO_THINK
}	t_philo_action;

typedef struct s_params
{
	t_usize	philo_count;
	t_usize	tt_die;
	t_usize	tt_sleep;
	t_usize	tt_eat;
	t_usize	eat_max;
}	t_params;

typedef struct s_sim
{
	t_sync_bool	*forks;
	t_philo		*philos;
	t_sync_bool	running;
	t_mutex		log_mutex;
}	t_sim;

void
*philo_handler(t_philo *philo);

#endif