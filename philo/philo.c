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

int	main(int argc, char **argv)
{
	t_main	args;

	if (argc == 5 || argc == 6)
	{
		if (init_args(&args, argc, argv) == 0)
			return (-1);
		if (init_philo(&args) == -1)
			return (-1);
		if (init_thread(&args) == -1)
			return (-1);
		end_thread(&args);
	}
	else
		printf("Error: There must be 4 or 5 arguments");
	return (0);
}
