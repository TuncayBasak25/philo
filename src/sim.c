/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:49:04 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 19:09:31 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"
#include "mem.h"
#include "mutex.h"
#include "thread.h"
#include "philo.h"

t_sim	new_sim(int philo_count, int tt_die, int tt_eat, int tt_sleep)
{
	t_sim	sim;
	int		i;

	sim = (t_sim){0};
	sim.philo_count = philo_count;
	sim.tt_die = tt_die;
	sim.tt_eat = tt_eat;
	sim.tt_sleep = tt_sleep;
	sim.eat_max = -1;
	sim.forks = mem_alloc(sizeof(t_mutex) * philo_count);
	sim.philos = mem_alloc(sizeof(t_philo) * philo_count);
	if (!sim.forks || !sim.philos)
		return (sim_destroy(&sim), sim);
	sim.log = new_mutex();
	i = -1;
	while (++i < philo_count)
		sim.forks[i] = new_mutex();
	return (sim);
}

void	sim_start(t_sim *self)
{
	int		i;

	self->start_time = time();
	i = -1;
	while (++i < self->philo_count)
	{
		self->philos[i] = new_philo(self, i + 1);
		philo_start(&self->philos[i]);
	}
}

void	drop_sim(t_sim sim)
{
	int	i;

	sim.stop = 1;
	i = -1;
	while (++i < sim.philo_count)
		thread_join(&sim.philos[i].thread);
	i = -1;
	while (++i < sim.philo_count)
		drop_mutex(sim.forks[i]);
	mem_free(sim.forks);
	mem_free(sim.philos);
	drop_mutex(sim.log);
}

void	sim_destroy(t_sim *self)
{
	drop_sim(*self);
	*self = (t_sim){0};
}
