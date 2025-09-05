/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_usage(void)
{
	ft_putstr_fd("Usage: ./philo nbr_philos t_die t_eat t_sleep ", 2);
	ft_putstr_fd("[must_eat]\n", 2);
}

int	main(int ac, char **av)
{
	t_sim	sim;

	if (ac != 5 && ac != 6)
	{
		print_usage();
		return (1);
	}
	if (!parse_and_init(ac, av, &sim))
	{
		ft_putstr_fd("Error: invalid arguments or init failed\n", 2);
		return (1);
	}
	start_sim(&sim);
	cleanup_sim(&sim);
	return (0);
}
