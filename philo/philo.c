/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:47:35 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/22 16:09:48 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_args(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: There must be 4 or 5 arguments\n");
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_is_digit(argv[i]) || (!ft_atoi(argv[i])))
		{
			printf("Invalid arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	args;

	if (valid_args(argc, argv))
		return (1);
	if (init_args(&args, argc, argv) == 1)
		return (1);
	init_mutex(&args);
	init_philo(&args);
	init_threads(&args);
	end_threads(&args);
	destroy_mutex(&args);
	free_args(&args);
	return (0);
}
