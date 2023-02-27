/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:22:37 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 20:01:14 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Manger*/
void	eat(t_philo *philo)
{
	long int	time;

	pick_forks(philo, philo->args);
	ft_log(philo, "has taken a fork");
	ft_log(philo, "has taken a fork");
	if (pthread_mutex_lock(&philo->args->m_meal) != 0)
		return ;
	time = ft_log(philo, "is eating");
	philo->last_meal = time;
	if (pthread_mutex_unlock(&philo->args->m_meal) != 0)
		return ;
	ft_usleep(philo->args->time_to_eat);
	release_forks(philo, philo->args);
	if (pthread_mutex_lock(&philo->args->m_meal) != 0)
		return ;
	if (philo->meals_to_eat > 0)
		philo->meals_to_eat--;
	if (pthread_mutex_unlock(&philo->args->m_meal) != 0)
		return ;
}

/*Un seul philosophe mange*/
void	one_eat(t_philo *philo)
{
	ft_log(philo, "has taken a fork");
	usleep(philo->args->time_to_die * 1000);
	printf("%ldms %d died\n", (ft_time() - \
	philo->args->start), philo->id);
}

/*Manger meals_to_eat fois*/
void	full_eat(t_philo *philo)
{
	while (is_alive(philo) == 1 && philo->meals_to_eat > 0)
	{		
		eat(philo);
		if (philo->meals_to_eat > 0)
			sleep_and_think(philo);
	}
	if (pthread_mutex_lock(&philo->args->m_meal) != 0)
		return ;
	philo->args->meals--;
	if (pthread_mutex_unlock(&philo->args->m_meal) != 0)
		return ;
}

/*Dormir et penser*/
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
