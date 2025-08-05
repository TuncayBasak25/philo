/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:48:27 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 19:09:23 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIM_H
# define SIM_H

# define _DEFAULT_SOURCE

# include "t_sim.h"
# include "t_philo_action.h"

t_sim
new_sim(int philo_count, int tt_die, int tt_eat, int tt_sleep);

void
drop_sim(t_sim sim);

void
sim_destroy(t_sim *self);

void
sim_log(t_sim *self, int philo_id, t_philo_action action);

void
sim_start(t_sim *self);

int	time(void);

#endif