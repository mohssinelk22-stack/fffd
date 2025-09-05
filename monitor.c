/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_done(t_sim *sim)
{
	int	done;

	pthread_mutex_lock(&sim->state_mtx);
	done = (sim->must_eat > 0 && sim->done_count >= sim->count);
	pthread_mutex_unlock(&sim->state_mtx);
	return (done);
}

static int	check_death(t_sim *sim, int i)
{
	long long	diff;
	long long	last;

	pthread_mutex_lock(&sim->philos[i].meal_mtx);
	last = sim->philos[i].last_meal_ms;
	pthread_mutex_unlock(&sim->philos[i].meal_mtx);
	diff = now_ms() - last;
	if (diff > sim->t_die)
	{
		print_state(sim, sim->philos[i].id, MSG_DIE, 1);
		set_stopped(sim, 1);
		return (1);
	}
	return (0);
}

void	monitor_sim(t_sim *sim)
{
	int	i;

	while (!get_stopped(sim))
	{
		if (sim->must_eat > 0 && all_done(sim))
		{
			set_stopped(sim, 1);
			break ;
		}
		i = 0;
		while (i < sim->count && !get_stopped(sim))
		{
			if (check_death(sim, i))
				return ;
			i++;
		}
		usleep(1000);
	}
}
