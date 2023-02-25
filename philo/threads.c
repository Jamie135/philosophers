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
	if (philo->data->nb_of_philo == 1)
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
int	thread_even(t_philo *philo_lst, int nb_philo)
{
	int	i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, \
		&get_action, &philo_lst[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

/*Initialiser les threads qui vont executer les routines des philosophes impairs*/
int	thread_odd(t_philo *philo_lst, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, \
		&get_action, &philo_lst[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

/*Initialiser les threads pour les philosophes pairs puis impairs*/
int	init_thread(t_data *data)
{
	data->start_time = ft_time();
	if (thread_even(data->philo_lst, data->nb_of_philo))
		return (-1);
	usleep(100);
	if (thread_odd(data->philo_lst, data->nb_of_philo))
		return (-1);
	if (data->nb_of_philo != 1 && data->nb_time_must_eat > 0)
		check_philo_death_n_meals(data);
	else
		check_philo_death(data);
	return (1);
}

void	end_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo_lst[i].thread, NULL);
		++i;
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->philo_lst[i].forks[i]);
		++i;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philo_lst->forks);
	free(data->philo_lst);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	return ;
}
