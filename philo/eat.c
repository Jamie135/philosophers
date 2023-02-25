/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:22:31 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 14:22:32 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_while_philo_need(t_philo *philo)
{
	while (is_alive(philo) == 1 && philo->nb_meal > 0)
	{		
		eat(philo);
		if (philo->nb_meal > 0)
			sleep_and_think(philo);
	}
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->data->nb_time_must_eat--;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	one_philo_eat(t_philo *philo)
{
	display(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	printf("%ldms %d died\n", (get_time() - \
	philo->data->start_time), philo->id);
}
