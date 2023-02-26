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

int	check_digits(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				if (argv[i][j] != '+')
				{
					printf("Error: Arguments must be positive numbers.\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_digits(int argc, char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[1]) == 0)
	{
		printf("Error: There must be at least one philosopher.\n");
		return (0);
	}
	while (i < argc)
	{
		if (ft_atol(argv[i]) > INT_MAX)
		{
			printf("Error: Arguments must not overflow.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (check_digits(argc, argv) == 0)
		return (0);
	if (valid_digits(argc, argv) == 0)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("Error: Not enough meals.\n");
		return (0);
	}
	return (1);
}

/*Initialiser les arguments et les mutex pour print, meal et death*/
int	init_args(t_main *args, int argc, char **argv)
{
	if (check_args(argc, argv) == 0)
		return (0);
	args->num = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->meals = ft_atoi(argv[5]);
	else if (argc == 5)
		args->meals = 0;
	args->dead = 0;
	pthread_mutex_init(&args->m_print, NULL);
	pthread_mutex_init(&args->m_meal, NULL);
	pthread_mutex_init(&args->m_death, NULL);
	return (1);
}

/*Initialiser les datas et les mutex pour chaque philosophes. La variable meals devient nb_philo_that_still_have_to_eat*/
int	init_philo(t_main *args)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * args->num);
	args->philosopher = malloc(sizeof(t_philo) * args->num);
	if (!forks || !args->philosopher)
	{
		free(forks);
		return (-1);
	}
	while (i < args->num)
	{
		args->philosopher[i].id = i + 1;
		args->philosopher[i].meals_to_eat = args->meals;
		args->philosopher[i].args = args;
		args->philosopher[i].forks = forks;
		args->philosopher[i].last_meal = ft_time();
		pthread_mutex_init(&args->philosopher[i].forks[i], NULL);
		i++;
	}
	args->meals = args->num;
	return (1);
}
