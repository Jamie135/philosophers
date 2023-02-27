/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:22:13 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 14:41:55 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Verifier si death est vrai ou si l'attente depasse time_to_die.*/
int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->m_death);
	if (philo->args->dead == 1)
	{
		pthread_mutex_unlock(&philo->args->m_death);
		return (0);
	}
	if (ft_time() - philo->last_meal >= philo->args->time_to_die)
	{
		pthread_mutex_unlock(&philo->args->m_death);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->m_death);
	return (1);
}

void	kill_philo(t_main *args, long int time, int i)
{
	pthread_mutex_lock(&args->m_death);
	args->dead = 1;
	pthread_mutex_unlock(&args->m_death);
	pthread_mutex_lock(&args->m_print);
	if (args->num > 1)
		printf("%ldms %d died\n", (time - \
	args->start), args->philosopher[i].id);
	pthread_mutex_unlock(&args->m_print);
}

/* Verifier quel philosophe est mort */
void	is_death(t_main *args)
{
	int			i;
	long int	time;

	i = 0;
	while (1)
	{
		time = ft_time();
		pthread_mutex_lock(&args->m_meal);
		if ((time - args->philosopher[i].last_meal) >= \
		(long int)args->time_to_die)
		{
			pthread_mutex_unlock(&args->m_meal);
			kill_philo(args, time, i);
			return ;
		}
		pthread_mutex_unlock(&args->m_meal);
		i++;
		if (i == (args->num - 1))
			i = 0;
		usleep(10);
	}
}

void	compare_times(struct s_philo *philo)
{
	long int	time;

	time = ft_time();
	pthread_mutex_lock(&philo->args->m_meal);
	if ((time - philo->last_meal) >= (long int)philo->args->time_to_die)
	{
		kill_philo(philo->args, time, philo->id);
	}
	pthread_mutex_unlock(&philo->args->m_meal);
}

void	dead_or_alive(t_main *args)
{
	int			i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&args->m_meal);
		if (args->meals == 0)
		{
			pthread_mutex_unlock(&args->m_meal);
			return ;
		}
		pthread_mutex_unlock(&args->m_meal);
		compare_times(&(args->philosopher[i]));
		if (args->dead == 1)
			return ;
		i++;
		if (i == (args->num - 1))
			i = 0;
		usleep(100);
	}
}
