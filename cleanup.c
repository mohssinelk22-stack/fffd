/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_sim(t_sim *sim)
{
	int	i;

	if (!sim)
		return ;
	i = 0;
	if (sim->forks)
	{
		while (i < sim->count)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&sim->print_mtx);
	pthread_mutex_destroy(&sim->state_mtx);
	if (sim->philos)
	{
		i = 0;
		while (i < sim->count)
		{
			pthread_mutex_destroy(&sim->philos[i].meal_mtx);
			i++;
		}
	}
	free(sim->forks);
	free(sim->philos);
}
