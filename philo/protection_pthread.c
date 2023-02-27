/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection_pthread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:21:00 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/27 19:46:46 by pbureera         ###   ########.fr       */
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
