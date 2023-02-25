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

typedef struct s_data
{
	long int		start_time;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_must_eat;
	bool			is_dead;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	struct s_philo	*philo_lst;
}				t_data;

typedef struct s_philo
{
	int					id;
	int					nb_meal;
	long int			last_meal;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t		*forks;
}				t_philo;

/* init.c */
int		check_digits(int ac, char **av);
int		valid_digits(int ac, char **av);
int		check_args(int ac, char **av);
int		init_args(t_data *data, int ac, char **av);
int		init_philo(t_data *data);

/* threads.c */
void	*get_action(void *arg);
int		thread_even(t_philo *philo_lst, int nb_philo);
int		thread_odd(t_philo *philo_lst, int nb_philo);
int		init_thread(t_data *data);
void	end_thread(t_data *data);

/*--------Routine---------*/
void	eat(t_philo *philo);
void	one_eat(t_philo *philo);
void	full_eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);

/*--------Forks---------*/
void	lock_forks(t_philo *philo, t_data *data);
void	unlock_forks(t_philo *philo, t_data *data);

/*--------End_simulation---------*/
int		is_alive(t_philo *philo);
void	kill_philo(t_data *data, long int actual_time, int i);
void	check_philo_death(t_data *data);
int		endofmeal(t_data *data);
void	check_philo_death_n_meals(t_data *data);

/*--------Time_functions---------*/
long	int	get_time(void);
void	handmade_usleep(long int timetosleep);
long	int	display(t_philo *philo, char *str);

/*--------utils.c---------*/
size_t	ft_strlen(char const *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif
