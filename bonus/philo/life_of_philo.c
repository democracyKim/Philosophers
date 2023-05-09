/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:15:39 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/09 11:24:48 by minkim3          ###   ########.fr       */
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

int	has_anyone_died(t_philo *philo)
{
	sem_wait(philo->resources->living);
	if (philo->resources->live == FALSE)
	{
		sem_post(philo->resources->living);
		return (TRUE);
	}
	sem_post(philo->resources->living);
	return (FALSE);
}

void	*life_of_philo(t_philo	*philo)
{
	sem_wait(philo->resources->start);
	sem_wait(philo->resources->last_meal);
	philo->last_meal_time = philo->info->start_time;
	sem_post(philo->resources->last_meal);
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
			return (NULL);
		sleeping(philo);
		thinking(philo);
		if (has_anyone_died(philo) == TRUE)
			return (NULL);
	}
	return (NULL);
}
