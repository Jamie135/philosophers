/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:21:20 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 19:21:28 by pbureera         ###   ########.fr       */
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
