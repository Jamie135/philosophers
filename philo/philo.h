/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:06:12 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 15:24:45 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR_ARGS "Error: There must be 4 or 5 arguments"

struct	s_arg;

typedef struct s_philo
{
	int				id;
	int				total_nbr_of_meals;
	int				total_nbr_of_meals_1;
	time_t			time_of_last_meal;
	int				nbr_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	time_t			limit_of_life;
	int				stop;
	time_t			start_time;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_arg	*arg;
}					t_philo;

typedef struct s_arg
{
	int				nbr_philo;
	int				id;
	time_t			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	int				nbr_of_meals;
	pthread_mutex_t	*forks;
	pthread_t		*tids;
	pthread_mutex_t	lock_print;
	t_philo			*all_philos;
}					t_arg;

void	get_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	dying(t_philo *philo, int i);
long	ft_time(void);
void	ft_usleep(int ms);
int		ft_atoi(const char *str);
int		ft_is_digit(char *str);
int		count_meals(t_philo *philo);
void	*ft_galina_monitor(void *args);
void	*do_process(void *args);
void	init_philo(t_arg *args);
void	init_mutex(t_arg *args);
void	init_threads(t_arg *args);
void	end_threads(t_arg *args);
int		init_args(t_arg *args, int argc, char **argv);
void	free_args(t_arg *args);
void	destroy_mutex(t_arg *args);

#endif
