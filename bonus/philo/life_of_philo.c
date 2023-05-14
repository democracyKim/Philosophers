/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:15:39 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/14 18:06:53 by minkim3          ###   ########.fr       */
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
	if (philo->id % 2 == 0)
		usleep(philo->info->time_to_eat);
	usleep(philo->id);
	while (TRUE)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(100);
	}
	return (NULL);
}
