/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:33:25 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 16:07:26 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_main *args)
{
	int	nbr_ph;

	nbr_ph = args->num;
	while (nbr_ph--)
	{
		pthread_mutex_unlock(&args->forks[nbr_ph]);
		pthread_mutex_destroy(&args->forks[nbr_ph]);
	}
	pthread_mutex_unlock(&(*args).lock);
	pthread_mutex_destroy(&(*args).lock);
}

void	free_args(t_main *args)
{
	free(args->tids);
	free(args->philosophers);
	free(args->forks);
}
