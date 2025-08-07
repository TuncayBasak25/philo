/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:15:37 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/07 14:57:16 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "thread.h"
#include <unistd.h>
#include <stdio.h>

static t_result	try_parse_params(t_usize ac, t_cvstr *args, t_params *out)
{
	t_params	res;

	if (!args || !out || ac < 5 || ac > 6)
		return (FAIL);
	if (try_cvstr_into_usize(args[1], &res.philo_count) == FAIL)
		return (FAIL);
	if (try_cvstr_into_usize(args[2], &res.tt_die) == FAIL)
		return (FAIL);
	if (try_cvstr_into_usize(args[3], &res.tt_eat) == FAIL)
		return (FAIL);
	if (try_cvstr_into_usize(args[4], &res.tt_sleep) == FAIL)
		return (FAIL);
	if (ac == 6)
	{
		if (try_cvstr_into_usize(args[5], &res.eat_max) == FAIL)
			return (FAIL);
	}
	else
		res.eat_max = -1;
	*out = res;
	return (OK);
}

static void	drop_sim(t_sim sim, t_usize philo_count)
{
	t_usize	i;

	if (sim.forks)
	{
		i = -1;
		while (++i < philo_count)
			drop_sync_bool(sim.forks[i]);
	}
	drop_sync_bool(sim.running);
	drop_mutex(sim.log_mutex);
	mem_free(sim.forks);
	mem_free(sim.philos);
}

static void	run_philo(t_sim *sim, t_params params, t_usize id)
{
	t_philo	*philo;

	philo = &sim->philos[id - 1];
	philo->id = id;
	philo->eat_count = 0;
	philo->tt_die = params.tt_die;
	philo->tt_eat = params.tt_eat;
	philo->tt_sleep = params.tt_sleep;
	philo->eat_max = params.eat_max;
	philo->running = &sim->running;
	philo->log_mutex = &sim->log_mutex;
	philo->left = &sim->forks[id - 1];
	if (id % 2)
		philo->left = &sim->forks[id % params.philo_count];
	philo->right = &sim->forks[id % params.philo_count];
	if (id % 2)
		philo->right = &sim->forks[id - 1];
	philo->thread = new_thread((t_fn_task)philo_handler, &sim->philos[id - 1]);
}

static void	run_sim(t_usize philo_count, t_params params)
{
	t_sim	sim;
	t_usize	i;
	t_usize	start_time;

	sim.forks = mem_alloc(sizeof(t_sync_bool) * philo_count);
	sim.philos = mem_alloc(sizeof(t_philo) * philo_count);
	sim.running = new_sync_bool(FALSE);
	sim.log_mutex = new_mutex();
	if (!sim.forks || !sim.philos || !sim.running.mutex.is_valid)
		return (log_error("Init error!\n"), drop_sim(sim, philo_count));
	i = -1;
	while (++i < philo_count)
		sim.forks[i] = new_sync_bool(TRUE);
	i = -1;
	while (++i < philo_count)
		run_philo(&sim, params, i + 1);
	i = -1;
	start_time = time_ms();
	while (++i < philo_count)
		sim.philos[i].start_time = start_time;
	sync_bool_set(&sim.running, TRUE);
	i = -1;
	while (++i < philo_count)
		thread_join(&sim.philos[i].thread);
	drop_sim(sim, philo_count);
}

t_i32	main(t_i32 ac, t_cvstr *args)
{
	t_params	params;

	if (try_parse_params(ac, args, &params) == FAIL)
		return (log_error("Invalid arguments!\n"), 1);
	run_sim(params.philo_count, params);
	return (0);
}
