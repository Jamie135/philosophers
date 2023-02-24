/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:21:33 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 14:35:20 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	data->philo_lst = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!forks || !data->philo_lst)
	{
		free(forks);
		return (-1);
	}
	while (i < data->nb_of_philo)
	{
		data->philo_lst[i].id = i + 1;
		data->philo_lst[i].nb_meal = data->nb_time_must_eat;
		data->philo_lst[i].data = data;
		data->philo_lst[i].forks = forks;
		data->philo_lst[i].last_meal = get_time();
		pthread_mutex_init(&data->philo_lst[i].forks[i], NULL);
		i++;
	}
	data->nb_time_must_eat = data->nb_of_philo;
	return (1);
}
