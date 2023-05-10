/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:15:39 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/10 14:58:54 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	time_lapse(philo->info->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
}

void	*life_of_philo(t_philo	*philo)
{
	sem_wait(philo->resources->start);
	if (pthread_create(philo->monitor, NULL, monitoring, \
		(void *)philo) == -1)
	{
		printf("Error: Failed to create monitoring thread\n");
		return (NULL);
	}
	while (TRUE)
	{
		usleep(philo->info->number_of_philosophers);
		if (eating(philo) != 0)
		{
			kill(philo->pid, SIGTERM);
			return (NULL);
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
