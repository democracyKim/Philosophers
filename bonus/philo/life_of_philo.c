/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:15:39 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/15 14:36:32 by minkim3          ###   ########.fr       */
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

void	*life_of_philo(t_philo *philo)
{
	sem_wait(philo->resources->start);
	if (pthread_create(philo->monitor, NULL, monitoring, (void *)philo) == -1)
	{
		printf("Error: Failed to create monitoring thread\n");
		return (NULL);
	}
	while (TRUE)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(100);
	}
	return (NULL);
}

int	start_life_of_philo(t_philo *philo, int i)
{
	philo[i].pid = fork();
	if (philo[i].pid == 0)
	{
		life_of_philo(&philo[i]);
	}
	else if (philo[i].pid < 0)
	{
		printf("Error: Failed to create process for philosopher %d.\n", i + 1);
		return (ERROR);
	}
	return (0);
}
