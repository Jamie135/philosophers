/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:33:25 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 16:14:20 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_main *args)
{
	int	n;

	n = args->num;
	while (n--)
	{
		pthread_mutex_unlock(&args->forks[n]);
		pthread_mutex_destroy(&args->forks[n]);
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
