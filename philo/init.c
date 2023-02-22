/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:39:29 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 16:13:21 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_main *args, int argc, char **argv)
{
	args->num = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->dead = 0;
	if (argc == 6)
		args->meals = ft_atoi(argv[5]);
	if (argc == 5)
	{
		if (args->num < 1)
			return (0);
		args->meals = -1;
	}
	if (argc == 6)
	{
		if (args->meals < 1)
			return (0);
	}
	return (0);
}

void	init_mutex(t_main *args)
{
	int				n;
	pthread_mutex_t	*mutex;

	n = args->num;
	mutex = malloc(sizeof(pthread_mutex_t) * n);
	while (n--)
		pthread_mutex_init(&mutex[n], NULL);
	pthread_mutex_init(&args->lock, NULL);
	args->forks = mutex;
}

void	init_philo(t_main *args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->num);
	while (i < args->num)
	{
		philos[i].id = i;
		philos[i].num = args->num;
		philos[i].eaten_meals = 0;
		philos[i].meals = args->meals;
		philos[i].time_to_eat = args->time_to_eat;
		philos[i].time_to_sleep = args->time_to_sleep;
		philos[i].time_to_die = args->time_to_die;
		philos[i].last_meal = ft_time();
		philos[i].lifespan = args->time_to_die;
		philos[i].stop = 0;
		philos[i].left_fork = &args->forks[philos[i].id];
		philos[i].right_fork = &args->forks[(philos[i].id + 1) % args->num];
		philos[i].arg = args;
		i++;
	}
	args->philosophers = philos;
}

void	init_threads(t_main *args)
{
	int			i;
	int			n;
	pthread_t	*threads;
	pthread_t	s_tid;

	i = 0;
	n = args->num;
	threads = malloc(sizeof(pthread_t) * n);
	while (i < n)
	{	
		pthread_create(&threads[i], \
			NULL, do_process, (void *)&args->philosophers[i]);
		i++;
	}
	pthread_create(&s_tid, NULL, ft_galina_monitor, (void *)args->philosophers);
	pthread_join(s_tid, NULL);
	args->tids = threads;
}

void	end_threads(t_main *args)
{
	int	n;

	n = args->num;
	if (n == 1)
	{
		pthread_mutex_unlock(&args->forks[0]);
	}
	while (n)
	{
		n--;
		pthread_join(args->tids[n], NULL);
	}
}
