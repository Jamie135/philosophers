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

int	thread_even(t_philo *philo_lst, int nb_philo)
{
	int	i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, \
		&routine, &philo_lst[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

int	thread_odd(t_philo *philo_lst, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, \
		&routine, &philo_lst[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

int	start(t_data *data)
{
	data->start_time = get_time();
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
