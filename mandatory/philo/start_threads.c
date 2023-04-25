/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:56:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/25 21:31:35 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_threads(t_philo *philo)
{
	int		i;
	t_info	*info;

	info = &(philo[0].info);
	i = 0;
	while (i < info->number_of_philosophers)
	{
		if (pthread_create(&(philo[i].threads), NULL, \
			life_of_philo, &philo[i]) != 0)
		{
			printf("Error: Failed to start thread \
				for philosopher %d.\n", i + 1);
			return (ERROR);
		}
		i++;
	}
	return (0);
}
