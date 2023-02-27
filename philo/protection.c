/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:21:00 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 20:18:59 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	protect_mutex(pthread_mutex_t *m, pthread_mutex_t *forks, t_philo *philo)
{
	if (pthread_mutex_init(m, NULL) != 0)
	{
		if (forks)
			free(forks);
		if (philo)
			free(philo);
		printf("Error: mutex failed.\n");
		return (-1);
	}
	return (0);
}

int	protect_malloc_forks(pthread_mutex_t *forks)
{
	if (!forks)
	{
		printf("Error: malloc failed.\n");
		return (0);
	}
	return (1);
}

int	protect_malloc_philo(t_philo *philo, pthread_mutex_t *forks)
{
	if (!philo)
	{
		free(forks);
		printf("Error: malloc failed.\n");
		return (0);
	}
	return (1);
}
