/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(int ac, char **av, t_sim *sim)
{
	long long	tmp;

	if (!ft_atoi_strict(av[1], &tmp) || tmp < 1 || tmp > 200)
		return (0);
	sim->count = (int)tmp;
	if (!ft_atoi_strict(av[2], &sim->t_die) || sim->t_die < 0)
		return (0);
	if (!ft_atoi_strict(av[3], &sim->t_eat) || sim->t_eat < 0)
		return (0);
	if (!ft_atoi_strict(av[4], &sim->t_sleep) || sim->t_sleep < 0)
		return (0);
	sim->must_eat = -1;
	if (ac == 6)
	{
		if (!ft_atoi_strict(av[5], &tmp) || tmp < 1 || tmp > 1000000)
			return (0);
		sim->must_eat = (int)tmp;
	}
	return (1);
}

static int	init_mutexes(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&sim->print_mtx, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&sim->state_mtx, NULL) != 0)
		return (0);
	return (1);
}

static void	assign_forks(t_sim *sim, int i)
{
	t_philo	*p;

	p = &sim->philos[i];
	p->left = &sim->forks[i];
	if (i == sim->count - 1)
		p->right = &sim->forks[0];
	else
		p->right = &sim->forks[i + 1];
	if (p->id % 2 == 0)
	{
		p->left = &sim->forks[i + 1 == sim->count ? 0 : i + 1];
		p->right = &sim->forks[i];
	}
}

static int	init_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->count)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].sim = sim;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal_ms = 0;
		if (pthread_mutex_init(&sim->philos[i].meal_mtx, NULL) != 0)
			return (0);
		assign_forks(sim, i);
		i++;
	}
	return (1);
}

int	parse_and_init(int ac, char **av, t_sim *sim)
{
	sim->forks = NULL;
	sim->philos = NULL;
	sim->stopped = 0;
	sim->done_count = 0;
	if (!parse_args(ac, av, sim))
		return (0);
	sim->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * sim->count);
	if (!sim->forks)
		return (0);
	sim->philos = (t_philo *)malloc(sizeof(t_philo) * sim->count);
	if (!sim->philos)
		return (0);
	if (!init_mutexes(sim) || !init_philos(sim))
		return (0);
	return (1);
}
