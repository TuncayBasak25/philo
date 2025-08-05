/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:19:44 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 19:20:13 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sim.h"
#include "philo.h"
#include "thread.h"
#include "mutex.h"
#include <unistd.h>

static void	take_forks(t_sim *sim, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_lock(philo->left);
		sim_log(sim, philo->id, PHILO_FORK);
		mutex_lock(philo->right);
		sim_log(sim, philo->id, PHILO_FORK);
	}
	else
	{
		mutex_lock(philo->right);
		sim_log(sim, philo->id, PHILO_FORK);
		mutex_lock(philo->left);
		sim_log(sim, philo->id, PHILO_FORK);
	}
}

static void	*task(t_philo *philo)
{
	t_sim	*sim;
	int		think_start;

	sim = philo->sim;
	while (!sim->stop && sim->eat_max > -1 && philo->eat_count < sim->eat_max)
	{
		take_forks(sim, philo);
		sim_log(sim, philo->id, PHILO_EAT);
		usleep(sim->tt_eat);
		mutex_unlock(philo->left);
		mutex_unlock(philo->right);
		sim_log(sim, philo->id, PHILO_SLEEP);
		usleep(sim->tt_sleep);
		sim_log(sim, philo->id, PHILO_THINK);
		think_start = time();
		while (time() - think_start < sim->tt_die)
	}
	return (0);
}

t_philo	new_philo(t_sim *sim, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.sim = sim;
	philo.eat_count = 0;
	philo.left = &sim->forks[id - 1];
	if (id == sim->philo_count)
		philo.right = &sim->forks[0];
	else
		philo.right = &sim->forks[id];
	return (philo);
}

void	philo_start(t_philo *self)
{
	if (self->sim->stop)
		return ;
	self->thread = new_thread(task, self);
	if (!self->thread.pthread)
		self->sim->stop;
}
