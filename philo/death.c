/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:22:13 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 14:22:14 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Verifier si death est vrai ou si l'attente depasse time_to_die, on arrete la routine dans ce cas*/
int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_death);
	if (philo->data->is_dead == true)
	{
		pthread_mutex_unlock(&philo->data->m_death);
		return (0);
	}
	if (ft_time() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->m_death);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->m_death);
	return (1);
}

void	kill_philo(t_data *data, long int actual_time, int i)
{
	pthread_mutex_lock(&data->m_death);
	data->is_dead = true;
	pthread_mutex_unlock(&data->m_death);
	pthread_mutex_lock(&data->m_print);
	if (data->num > 1)
		printf("%ldms %d died\n", (actual_time - \
	data->start), data->philosopher[i].id);
	pthread_mutex_unlock(&data->m_print);
}

/* Verifier death pour nb_philo = 1*/
void	is_death(t_data *data)
{
	int			i;
	long int	actual_time;

	i = 0;
	while (1)
	{
		actual_time = ft_time();
		pthread_mutex_lock(&data->m_meal);
		if ((actual_time - data->philosopher[i].last_meal) >= \
		(long int)data->time_to_die)
		{
			pthread_mutex_unlock(&data->m_meal);
			kill_philo(data, actual_time, i);
			return ;
		}
		pthread_mutex_unlock(&data->m_meal);
		i++;
		if (i == (data->num - 1))
			i = 0;
		usleep(10);
	}
}

void	compare_times(struct s_philo *philo)
{
	long int	actual_time;

	actual_time = ft_time();
	pthread_mutex_lock(&philo->data->m_meal);
	if ((actual_time - philo->last_meal) >= (long int)philo->data->time_to_die)
	{
		kill_philo(philo->data, actual_time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->m_meal);
}

void	dead_or_alive(t_data *data)
{
	int			i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->m_meal);
		if (data->meals == 0)
		{
			pthread_mutex_unlock(&data->m_meal);
			return ;
		}
		pthread_mutex_unlock(&data->m_meal);
		compare_times(&(data->philosopher[i]));
		if (data->is_dead == true)
			return ;
		i++;
		if (i == (data->num - 1))
			i = 0;
		usleep(100);
	}
}
