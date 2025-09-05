/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi_strict(const char *s, long long *out)
{
	long long	n;
	int			i;

	i = 0;
	n = 0;
	if (!s || !s[0])
		return (0);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == '+')
		i++;
	if (!is_digit(s[i]))
		return (0);
	while (is_digit(s[i]))
	{
		n = n * 10 + (s[i] - '0');
		if (n > 2147483647)
			return (0);
		i++;
	}
	if (s[i] != '\0')
		return (0);
	*out = n;
	return (1);
}

void	ft_putstr_fd(const char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
}

static void	putnbr_rec(long long n, int fd)
{
	char	c;

	if (n >= 10)
		putnbr_rec(n / 10, fd);
	c = '0' + (char)(n % 10);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long long n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	putnbr_rec(n, fd);
}

void	ft_putnbr_ll(long long n)
{
	ft_putnbr_fd(n, 1);
}
