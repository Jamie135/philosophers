/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:20:45 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 14:20:46 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (parsing(&data, ac, av) == 0)
			return (-1);
		if (init_philo(&data) == -1)
			return (-1);
		if (start(&data) == -1)
			return (-1);
		end(&data);
	}
	else
		printf("Error: Wrong amount of arguments.");
	return (0);
}
