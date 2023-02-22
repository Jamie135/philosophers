/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:09:52 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 15:53:01 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is eating\n", \
		ft_time() - philo->start, philo->id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	philo->eaten_meals += 1;
	philo->last_meal = ft_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is sleeping\n", \
		ft_time() - philo->start, philo->id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is thinking\n", \
		ft_time() - philo->start, philo->id + 1);
	pthread_mutex_unlock(&philo->lock_print);
}

void	dying(t_philo *philo, int i)
{
	philo->arg->dead = 1;
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d died\n", ft_time() - philo->start,
		philo[i].id + 1);
	i = -1;
	while (i < philo[i].num)
	{
		philo[i].stop = 1;
		i++;
	}
}
