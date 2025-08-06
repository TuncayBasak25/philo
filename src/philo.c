/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:19:44 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/07 01:05:30 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static t_bool	is_dead(t_philo *philo)
{
	return (time_ms() - philo->last_meal >= philo->tt_die);
}

static void	log_philo(t_philo *philo, t_philo_action action)
{
	t_usize	stamp;

	mutex_lock(philo->log_mutex);
	if (!sync_bool_get(philo->running))
		return (mutex_unlock(philo->log_mutex));
	stamp = time_ms() - philo->start_time;
	if (action == PHILO_DIE)
	{
		printf("%llu %llu DIED\n", stamp, philo->id);
		sync_bool_set(philo->running, FALSE);
	}
	else if (action == PHILO_FORK)
		printf("%llu %llu HAS TAKEN A FORK\n", stamp, philo->id);
	else if (action == PHILO_EAT)
		printf("%llu %llu IS EATING\n", stamp, philo->id);
	else if (action == PHILO_SLEEP)
		printf("%llu %llu IS SLEEPING\n", stamp, philo->id);
	else if (action == PHILO_THINK)
		printf("%llu %llu IS THINKING\n", stamp, philo->id);
	mutex_unlock(philo->log_mutex);
}

static t_result	take_forks(t_philo *philo)
{
	while (TRUE)
	{
		if (!sync_bool_get(philo->running))
			return (FAIL);
		if (is_dead(philo))
			return (log_philo(philo, PHILO_DIE), FAIL);
		if (sync_bool_cas(philo->left, TRUE, FALSE) == OK)
			break ;
		usleep(1);
	}
	log_philo(philo, PHILO_FORK);
	while (TRUE)
	{
		if (!sync_bool_get(philo->running))
			return (FAIL);
		if (is_dead(philo))
			return (log_philo(philo, PHILO_DIE), FAIL);
		if (sync_bool_cas(philo->right, TRUE, FALSE) == OK)
			break ;
		usleep(1);
	}
	log_philo(philo, PHILO_FORK);
	return (OK);
}

void	*philo_handler(t_philo *philo)
{
	while (!sync_bool_get(philo->running))
		usleep(1);
	philo->last_meal = philo->start_time;
	while (philo->eat_count++ < philo->eat_max && take_forks(philo) == OK)
	{
		log_philo(philo, PHILO_EAT);
		usleep(philo->tt_eat * 1000);
		sync_bool_set(philo->left, TRUE);
		sync_bool_set(philo->right, TRUE);
		philo->last_meal = time_ms();
		log_philo(philo, PHILO_SLEEP);
		usleep(philo->tt_sleep * 1000);
		log_philo(philo, PHILO_THINK);
	}
	return (0);
}
