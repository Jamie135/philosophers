/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:21:20 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 19:05:28 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	protect_mutex(pthread_mutex_t *m)
{
	if (pthread_mutex_init(m, NULL) != 0)
	{
		printf("Error: mutex failed.\n");
		return (-1);
	}
	return (0);
}
