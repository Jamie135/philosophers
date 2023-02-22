/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:59:03 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 16:06:58 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_meals(t_philo *philo)
{
	int	flag_enough;
	int	i;

	if (philo->eaten_meals != -1 \
		&& philo->meals > 0)
	{
		flag_enough = 1;
		i = -1;
		while (++i < philo->num)
			if (philo[i].eaten_meals < philo->meals)
				flag_enough = 0;
		if (flag_enough == 1)
		{
			i = -1;
			while (i < philo[i].num)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	*do_process(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->last_meal = ft_time();
	philo->start = ft_time();
	while (!philo->arg->dead)
	{
		if (philo->arg->dead || philo->stop || count_meals(philo))
			return (NULL);
		get_fork(philo);
		if (philo->arg->dead || philo->stop || count_meals(philo))
			return (NULL);
		eating(philo);
		if (philo->arg->dead || philo->stop || count_meals(philo))
			return (NULL);
		sleeping(philo);
		if (philo->arg->dead || philo->stop || count_meals(philo))
			return (NULL);
		thinking(philo);
		if (philo->arg->dead || philo->stop || count_meals(philo))
			return (NULL);
	}
	return (NULL);
}

void	*ft_galina_monitor(void *args)
{
	t_philo	*philo;
	long	time_now;
	int		i;

	philo = (t_philo *)args;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = -1;
		while (++i < philo->num)
		{
			time_now = ft_time();
			if (time_now - philo[i].last_meal > philo[i].lifespan)
			{
				dying(philo, i);
				pthread_mutex_unlock(&philo->lock);
				return (NULL);
			}
		}
		if (count_meals(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}
