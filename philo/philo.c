/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:20:45 by pbureera          #+#    #+#             */
/*   Updated: 2023/02/24 15:09:14 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (init_args(&data, ac, av) == 0)
			return (-1);
		if (init_philo(&data) == -1)
			return (-1);
		if (init_thread(&data) == -1)
			return (-1);
		end_thread(&data);
	}
	else
		printf("Error: There must be 4 or 5 arguments");
	return (0);
}
