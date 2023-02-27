/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:20:23 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 19:44:21 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_main
{
	long int		start;
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				dead;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_death;
	struct s_philo	*philosopher;
}				t_main;

typedef struct s_philo
{
	int					id;
	int					meals_to_eat;
	long int			last_meal;
	pthread_t			thread;
	t_main				*args;
	pthread_mutex_t		*forks;
}				t_philo;

/* init.c */
int		check_digits(int argc, char **argv);
int		valid_digits(int argc, char **argv);
int		check_args(int argc, char **argv);
int		init_args(t_main *args, int argc, char **argv);
int		init_philo(t_main *args);

/* threads.c */
void	*get_action(void *arg);
int		thread_even(t_philo *philosopher, int num);
int		thread_odd(t_philo *philosopher, int num);
int		init_thread(t_main *args);
void	end_thread(t_main *args);

/* actions.c */
void	eat(t_philo *philo);
void	one_eat(t_philo *philo);
void	full_eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);

/* forks.c */
void	pick_forks(t_philo *philo, t_main *args);
void	release_forks(t_philo *philo, t_main *args);

/* time.c */
long	int	ft_time(void);
void	ft_usleep(long int sleep);
long	int	ft_log(t_philo *philo, char *str);

/* death.c */
int		is_alive(t_philo *philo);
void	kill_philo(t_main *args, long int time, int i);
void	is_death(t_main *args);
void	dead_or_alive(t_main *args);

/* protection_malloc.c */
int		protect_malloc_philo(t_philo *philo, pthread_mutex_t *forks);
int		protect_malloc_forks(pthread_mutex_t *forks);

/* protection_pthread.c */
int		protect_mutex(pthread_mutex_t *m, \
						pthread_mutex_t *forks, t_philo *philo);

/* utils.c */
int		ft_isspace(int c);
size_t	ft_strlen(char const *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

#endif
