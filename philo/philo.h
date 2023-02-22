/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:06:12 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 16:00:29 by pbureera         ###   ########.fr       */
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

struct	s_main;

typedef struct s_philo
{
	int				num;
	int				id;
	int				eaten_meals;
	int				meals;
	time_t			last_meal;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	time_t			start;
	int				stop;
	time_t			lifespan;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_main	*arg;
}					t_philo;

typedef struct s_main
{
	int				num;
	int				id;
	int				meals;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	time_t			start;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_t		*tids;
	pthread_mutex_t	lock_print;
	t_philo			*philosophers;
}					t_main;

/* init.c */
int		init_args(t_main *args, int argc, char **argv);
void	init_mutex(t_main *args);
void	init_philo(t_main *args);
void	init_threads(t_main *args);
void	end_threads(t_main *args);

/* process */
int		count_meals(t_philo *philo);
void	*do_process(void *args);
void	*ft_galina_monitor(void *args);

/* forks.c */
void	get_fork_1(t_philo *philo);
void	get_fork_2(t_philo *philo);
void	get_fork(t_philo *philo);

/* status.c */
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	dying(t_philo *philo, int i);

/* utils.c */
long	ft_time(void);
void	ft_usleep(int ms);
int		ft_atoi(const char *str);
int		ft_is_digit(char *str);

/* free.c */
void	free_args(t_main *args);
void	destroy_mutex(t_main *args);

#endif
