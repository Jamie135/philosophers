/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:55:30 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 15:52:48 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork_1(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start, philo->id + 1);
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

void	get_fork_2(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start, philo->id + 1);
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

void	get_fork(t_philo *philo)
{
	if ((philo->id) % 2 == 0 && philo->id + 1 != philo->num)
		get_fork_1(philo);
	else
		get_fork_2(philo);
}
