/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:22:49 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 20:18:47 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Retourner le temps actuel em ms*/
long int	ft_time(void)
{
	long int		timestamp;
	struct timeval	time;

	timestamp = 0;
	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp);
}

/*Fonction usleep en ms*/
void	ft_usleep(long int sleep)
{
	long int	start;
	long int	time;
	long int	end;

	start = ft_time();
	end = start + sleep;
	while (1)
	{
		time = ft_time();
		if (time >= end)
			break ;
		usleep(100);
	}
}

/*Afficher les logs et update time pour last_meal*/
long int	ft_log(t_philo *philo, char *str)
{
	long int	time;

	time = ft_time();
	if (is_alive(philo) == 0)
		return (0);
	if (pthread_mutex_lock(&philo->args->m_print) != 0)
		return (0);
	printf("%ldms %d %s\n", (time - \
	philo->args->start), philo->id, str);
	if (pthread_mutex_unlock(&philo->args->m_print) != 0)
		return (0);
	return (time);
}
