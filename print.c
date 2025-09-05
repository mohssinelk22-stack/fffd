/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_space(void)
{
	write(1, " ", 1);
}

static void	put_newline(void)
{
	write(1, "\n", 1);
}

void	print_state(t_sim *sim, int id, const char *msg, int final)
{
	long long	ts;

	pthread_mutex_lock(&sim->print_mtx);
	if (!get_stopped(sim) || final)
	{
		ts = now_ms() - sim->start_ms;
		ft_putnbr_fd(ts, 1);
		put_space();
		ft_putnbr_fd(id, 1);
		put_space();
		ft_putstr_fd(msg, 1);
		put_newline();
	}
	pthread_mutex_unlock(&sim->print_mtx);
}
