/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_stopped(t_sim *sim)
{
	int	v;

	pthread_mutex_lock(&sim->state_mtx);
	v = sim->stopped;
	pthread_mutex_unlock(&sim->state_mtx);
	return (v);
}

void	set_stopped(t_sim *sim, int v)
{
	pthread_mutex_lock(&sim->state_mtx);
	sim->stopped = v;
	pthread_mutex_unlock(&sim->state_mtx);
}

void	increment_done(t_sim *sim)
{
	pthread_mutex_lock(&sim->state_mtx);
	sim->done_count += 1;
	pthread_mutex_unlock(&sim->state_mtx);
}

static void	*single_philo(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	print_state(p->sim, p->id, MSG_FORK, 0);
	pthread_mutex_lock(p->left);
	ft_usleep_ms(p->sim->t_die);
	pthread_mutex_unlock(p->left);
	return (NULL);
}

void	start_sim(t_sim *sim)
{
	int	i;

	sim->start_ms = now_ms();
	i = 0;
	while (i < sim->count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_mtx);
		sim->philos[i].last_meal_ms = sim->start_ms;
		pthread_mutex_unlock(&sim->philos[i].meal_mtx);
		if (sim->count == 1)
		{
			if (pthread_create(&sim->philos[i].thread, NULL, single_philo,
					&sim->philos[i]) != 0)
				set_stopped(sim, 1);
		}
		else if (pthread_create(&sim->philos[i].thread, NULL, philo_routine,
				&sim->philos[i]) != 0)
			set_stopped(sim, 1);
		i++;
	}
	monitor_sim(sim);
	i = 0;
	while (i < sim->count)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}
