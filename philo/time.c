/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:22:49 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 14:22:50 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_time(void)
{
	long int		timestamp;
	struct timeval	time;

	timestamp = 0;
	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp);
}

void	ft_usleep(long int timetosleep)
{
	long int	start;
	long int	actual_time;
	long int	end;

	start = ft_time();
	end = start + timetosleep;
	while (1)
	{
		actual_time = ft_time();
		if (actual_time >= end)
			break ;
		usleep(100);
	}
}

/*Afficher les logs et update actual_time apres avoir mange/dormi/pense*/
long int	ft_log(t_philo *philo, char *str)
{
	long int	actual_time;

	actual_time = ft_time();
	if (is_alive(philo) == 0)
		return (0);
	pthread_mutex_lock(&philo->args->m_print);
	printf("%ldms %d %s\n", (actual_time - \
	philo->args->start), philo->id, str);
	pthread_mutex_unlock(&philo->args->m_print);
	return (actual_time);
}
