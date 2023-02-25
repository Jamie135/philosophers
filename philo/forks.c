/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:22:08 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 14:22:09 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id % data->num]);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->forks[philo->id % data->num]);
	}
}

void	release_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks[philo->id % data->num]);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->forks[philo->id % data->num]);
	}
}
