/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:21:15 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 15:08:19 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digits(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("Error: arguments must be digit caracters.\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_digits(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) > INT_MAX || ft_strlen(av[i]) > 11)
		{
			printf("Error: int overflow.\n");
			return (0);
		}
		if (ft_atoi(av[i]) < 1)
		{
			printf("Error: invalid amount of philosophers.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (check_digits(ac, av) == 0)
		return (0);
	if (valid_digits(ac, av) == 0)
		return (0);
	if (ac == 6 && ft_atoi(av[5]) < 1)
	{
		printf("Error: not enough meals\n");
		return (0);
	}
	return (1);
}

/*Initialiser les arguments et les mutex pour print, meal et death*/
int	init_args(t_data *data, int ac, char **av)
{
	if (check_args(ac, av) == 0)
		return (0);
	data->num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals = ft_atoi(av[5]);
	else if (ac == 5)
		data->meals = 0;
	data->is_dead = false;
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_meal, NULL);
	pthread_mutex_init(&data->m_death, NULL);
	return (1);
}

/*Initialiser les datas et les mutex pour chaque philosophes. La variable nb_time_must_eat devient nb_philo_that_still_have_to_eat*/
int	init_philo(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->num);
	data->philosopher = malloc(sizeof(t_philo) * data->num);
	if (!forks || !data->philosopher)
	{
		free(forks);
		return (-1);
	}
	while (i < data->num)
	{
		data->philosopher[i].id = i + 1;
		data->philosopher[i].nb_meal = data->meals;
		data->philosopher[i].data = data;
		data->philosopher[i].forks = forks;
		data->philosopher[i].last_meal = ft_time();
		pthread_mutex_init(&data->philosopher[i].forks[i], NULL);
		i++;
	}
	data->meals = data->num;
	return (1);
}
