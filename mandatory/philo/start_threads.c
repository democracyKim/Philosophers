/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:56:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 22:33:10 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	start_odd_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&(philo[i].threads), NULL, life_of_philo,
					&philo[i]) != 0)
			{
				printf("Error: Failed to start thread \
					for philosopher %d.\n", i + 1);
				return (ERROR);
			}
		}
		i += 2;
	}
	return (0);
}

static int	start_even_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = 1;
	while (i < info->number_of_philosophers)
	{
		if (i & 1)
		{
			if (pthread_create(&(philo[i].threads), NULL, life_of_philo,
					&philo[i]) != 0)
			{
				printf("Error: Failed to start \
					thread for philosopher %d.\n", i + 1);
				return (ERROR);
			}
		}
		i += 2;
	}
	return (0);
}

int	start_threads(t_philo *philo)
{
	t_info	*info;

	info = &(philo[0].info);
	if (start_odd_philo(philo, info) == ERROR)
		return (ERROR);
	if (start_even_philo(philo, info) == ERROR)
		return (ERROR);
	pthread_mutex_unlock(&philo->resources->stop);
	return (0);
}
