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

	pick_forks(philo, philo->args);
	ft_log(philo, "has taken a fork");
	ft_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->args->m_meal);
	actual_time = ft_log(philo, "is eating");
	philo->last_meal = actual_time;
	pthread_mutex_unlock(&philo->args->m_meal);
	ft_usleep(philo->args->time_to_eat);
	release_forks(philo, philo->args);
	pthread_mutex_lock(&philo->args->m_meal);
	if (philo->meals_to_eat > 0)
		philo->meals_to_eat--;
	pthread_mutex_unlock(&philo->args->m_meal);
}

/* Un seul philosophe mange */
void	one_eat(t_philo *philo)
{
	ft_log(philo, "has taken a fork");
	usleep(philo->args->time_to_die * 1000);
	printf("%ldms %d died\n", (ft_time() - \
	philo->args->start), philo->id);
}

/* Manger jusqu'a nb_meals */
void	full_eat(t_philo *philo)
{
	while (is_alive(philo) == 1 && philo->meals_to_eat > 0)
	{		
		eat(philo);
		if (philo->meals_to_eat > 0)
			sleep_and_think(philo);
	}
	pthread_mutex_lock(&philo->args->m_meal);
	philo->args->meals--;
	pthread_mutex_unlock(&philo->args->m_meal);
}

void	sleep_and_think(t_philo *philo)
{
	if (is_alive(philo) == 0)
		return ;
	ft_log(philo, "is sleeping");
	ft_usleep(philo->args->time_to_sleep);
	if (is_alive(philo) == 0)
		return ;
	ft_log(philo, "is thinking");
	usleep(((philo->args->time_to_die - (philo->args->time_to_eat \
	+ philo->args->time_to_sleep)) / 2) * 1000);
}
