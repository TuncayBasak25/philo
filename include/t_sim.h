/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sim.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:48:27 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 18:32:06 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SIM_H
# define T_SIM_H

# include "t_mutex.h"

typedef struct s_sim
{
	int				philo_count;
	int				tt_die;
	int				tt_sleep;
	int				tt_eat;
	int				eat_max;
	int				start_time;
	int				stop;
	t_mutex			log;
	t_mutex			*forks;
	struct s_philo	*philos;
}	t_sim;

#endif