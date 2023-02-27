/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:22:44 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 14:55:22 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*get_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->args->num == 1)
	{
		one_eat(philo);
		return (0);
	}
	if (philo->meals_to_eat == 0)
	{
		while (is_alive(philo) == 1)
		{		
			eat(philo);
			sleep_and_think(philo);
		}
		return (0);
	}
	else
	{
		full_eat(philo);
		return (0);
	}
}

/*Init les threads qui vont executer les actions des philo pairs*/
int	thread_even(t_philo *philosopher, int num)
{
	int	i;

	i = 1;
	while (i < num)
	{
		if (pthread_create(&philosopher[i].thread, NULL, \
		&get_action, &philosopher[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

/*Init les threads qui vont executer les actions des philo impairs*/
int	thread_odd(t_philo *philosopher, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_create(&philosopher[i].thread, NULL, \
		&get_action, &philosopher[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

/*Initialiser les threads pour les philosophes pairs puis impairs*/
int	init_thread(t_main *args)
{
	args->start = ft_time();
	if (thread_even(args->philosopher, args->num))
		return (-1);
	usleep(100);
	if (thread_odd(args->philosopher, args->num))
		return (-1);
	if (args->num != 1 && args->meals > 0)
		dead_or_alive(args);
	else
		is_death(args);
	return (1);
}

/*Attendre l'execution de chaque thread philo[i] afin de
destroy et free les mutex et les variables*/
void	end_thread(t_main *args)
{
	int	i;

	i = 0;
	while (i < args->num)
	{
		pthread_join(args->philosopher[i].thread, NULL);
		++i;
	}
	i = 0;
	while (i < args->num)
	{
		pthread_mutex_destroy(&args->philosopher[i].forks[i]);
		++i;
	}
	pthread_mutex_destroy(&args->m_print);
	free(args->philosopher->forks);
	free(args->philosopher);
	pthread_mutex_destroy(&args->m_meal);
	pthread_mutex_destroy(&args->m_death);
	return ;
}
