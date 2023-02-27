/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:22:08 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 20:07:39 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Prendre deux fourchettes*/
void	pick_forks(t_philo *philo, t_main *args)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->forks[philo->id % args->num]) != 0)
			return ;
		if (pthread_mutex_lock(&philo->forks[philo->id - 1]) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_lock(&philo->forks[philo->id - 1]) != 0)
			return ;
		if (pthread_mutex_lock(&philo->forks[philo->id % args->num]) != 0)
			return ;
	}
}

/*Lacher les deux fourchettes*/
void	release_forks(t_philo *philo, t_main *args)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_unlock(&philo->forks[philo->id % args->num]) != 0)
			return ;
		if (pthread_mutex_unlock(&philo->forks[philo->id - 1]) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_unlock(&philo->forks[philo->id - 1]) != 0)
			return ;
		if (pthread_mutex_unlock(&philo->forks[philo->id % args->num]) != 0)
			return ;
	}
}
