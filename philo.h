/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by 42AI              #+#    #+#             */
/*   Updated: 2025/09/05 00:00:00 by 42AI             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/time.h>
# include <pthread.h>

# define MSG_FORK      "has taken a fork"
# define MSG_EAT       "is eating"
# define MSG_SLEEP     "is sleeping"
# define MSG_THINK     "is thinking"
# define MSG_DIE       "died"

typedef struct s_sim t_sim;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long long		last_meal_ms;
	int				meals_eaten;
	pthread_mutex_t	meal_mtx;
	t_sim			*sim;
}	t_philo;

struct s_sim
{
	int				count;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	int				must_eat; /* -1 if unlimited */
	long long		start_ms;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	state_mtx;
	int				stopped; /* 0 running, 1 stopped */
	int				done_count;
	t_philo			*philos;
};

int			parse_and_init(int ac, char **av, t_sim *sim);
void		start_sim(t_sim *sim);
void		*philo_routine(void *arg);
void		monitor_sim(t_sim *sim);

/* printing */
void		print_state(t_sim *sim, int id, const char *msg, int final);

/* actions */
void		philo_take_forks(t_philo *p);
void		philo_eat(t_philo *p);
void		philo_sleep_think(t_philo *p);

/* time utils */
long long	now_ms(void);
void		ft_usleep_ms(long long ms);

/* num utils */
int			ft_atoi_strict(const char *s, long long *out);
void		ft_putnbr_ll(long long n);
void		ft_putnbr_fd(long long n, int fd);
void		ft_putstr_fd(const char *s, int fd);

/* cleanup */
void		cleanup_sim(t_sim *sim);

/* state helpers */
int			get_stopped(t_sim *sim);
void		set_stopped(t_sim *sim, int v);
void		increment_done(t_sim *sim);

#endif
