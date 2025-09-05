/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_meal(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mtx);
	p->last_meal_ms = now_ms();
	pthread_mutex_unlock(&p->meal_mtx);
}

void	philo_take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->right);
		print_state(p->sim, p->id, MSG_FORK, 0);
		pthread_mutex_lock(p->left);
		print_state(p->sim, p->id, MSG_FORK, 0);
	}
	else
	{
		pthread_mutex_lock(p->left);
		print_state(p->sim, p->id, MSG_FORK, 0);
		pthread_mutex_lock(p->right);
		print_state(p->sim, p->id, MSG_FORK, 0);
	}
}

void	philo_eat(t_philo *p)
{
	print_state(p->sim, p->id, MSG_EAT, 0);
	update_meal(p);
	ft_usleep_ms(p->sim->t_eat);
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
	p->meals_eaten += 1;
	if (p->sim->must_eat > 0 && p->meals_eaten == p->sim->must_eat)
		increment_done(p->sim);
}

void	philo_sleep_think(t_philo *p)
{
	print_state(p->sim, p->id, MSG_SLEEP, 0);
	ft_usleep_ms(p->sim->t_sleep);
	print_state(p->sim, p->id, MSG_THINK, 0);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (!get_stopped(p->sim))
	{
		philo_take_forks(p);
		philo_eat(p);
		if (get_stopped(p->sim))
			break ;
		philo_sleep_think(p);
	}
	return (NULL);
}
