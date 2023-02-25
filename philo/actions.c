/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:22:37 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 14:22:38 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	long int	actual_time;

	lock_forks(philo, philo->data);
	display(philo, "has taken a fork");
	display(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal_mutex);
	actual_time = display(philo, "is eating");
	philo->last_meal = actual_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	handmade_usleep(philo->data->time_to_eat);
	unlock_forks(philo, philo->data);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->nb_meal > 0)
		philo->nb_meal--;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

/* Un seul philosophe mange */
void	one_eat(t_philo *philo)
{
	display(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	printf("%ldms %d died\n", (get_time() - \
	philo->data->start_time), philo->id);
}

/* Manger jusqu'a nb_meals */
void	full_eat(t_philo *philo)
{
	while (is_alive(philo) == 1 && philo->nb_meal > 0)
	{		
		eat(philo);
		if (philo->nb_meal > 0)
			sleep_and_think(philo);
	}
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->data->nb_time_must_eat--;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	sleep_and_think(t_philo *philo)
{
	if (is_alive(philo) == 0)
		return ;
	display(philo, "is sleeping");
	handmade_usleep(philo->data->time_to_sleep);
	if (is_alive(philo) == 0)
		return ;
	display(philo, "is thinking");
	usleep(((philo->data->time_to_die - (philo->data->time_to_eat \
	+ philo->data->time_to_sleep)) / 2) * 1000);
}
