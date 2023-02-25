/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:20:23 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 15:15:27 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_main
{
	long int		start;
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	bool			dead;
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
int		thread_even(t_philo *philosopher, int nb_philo);
int		thread_odd(t_philo *philosopherz, int nb_philo);
int		init_thread(t_main *args);
void	end_thread(t_main *args);

/*--------Routine---------*/
void	eat(t_philo *philo);
void	one_eat(t_philo *philo);
void	full_eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);

/*--------Forks---------*/
void	pick_forks(t_philo *philo, t_main *args);
void	release_forks(t_philo *philo, t_main *args);

/*--------End_simulation---------*/
int		is_alive(t_philo *philo);
void	kill_philo(t_main *args, long int actual_time, int i);
void	is_death(t_main *args);
void	dead_or_alive(t_main *args);

/*--------Time_functions---------*/
long	int	ft_time(void);
void	ft_usleep(long int timetosleep);
long	int	ft_log(t_philo *philo, char *str);

/*--------utils.c---------*/
size_t	ft_strlen(char const *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif
