/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:22:44 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 15:19:59 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*get_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num == 1)
	{
		one_eat(philo);
		return (0);
	}
	if (philo->nb_meal == 0)
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

/*Initialiser les threads qui vont executer les routines des philosophes pairs*/
int	thread_even(t_philo *philosopher, int nb_philo)
{
	int	i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&philosopher[i].thread, NULL, \
		&get_action, &philosopher[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

/*Initialiser les threads qui vont executer les routines des philosophes impairs*/
int	thread_odd(t_philo *philosopher, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philosopher[i].thread, NULL, \
		&get_action, &philosopher[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

/*Initialiser les threads pour les philosophes pairs puis impairs*/
int	init_thread(t_data *data)
{
	data->start = ft_time();
	if (thread_even(data->philosopher, data->num))
		return (-1);
	usleep(100);
	if (thread_odd(data->philosopher, data->num))
		return (-1);
	if (data->num != 1 && data->meals > 0)
		dead_or_alive(data);
	else
		is_death(data);
	return (1);
}

void	end_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		pthread_join(data->philosopher[i].thread, NULL);
		++i;
	}
	i = 0;
	while (i < data->num)
	{
		pthread_mutex_destroy(&data->philosopher[i].forks[i]);
		++i;
	}
	pthread_mutex_destroy(&data->m_print);
	free(data->philosopher->forks);
	free(data->philosopher);
	pthread_mutex_destroy(&data->m_meal);
	pthread_mutex_destroy(&data->m_death);
	return ;
}
