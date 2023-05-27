/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:58:36 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/27 18:09:20 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	time_lapse(philo->info.time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
}

static int	has_anyone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->living);
	if (philo->resources->live == FALSE)
	{
		pthread_mutex_unlock(&philo->resources->living);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->resources->living);
	return (FALSE);
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->info.time_to_eat);
	while (TRUE)
	{
		if (eating(philo) != 0)
			return (NULL);
		sleeping(philo);
		thinking(philo);
		if (has_anyone_died(philo) == TRUE)
			return (NULL);
		usleep(philo->info.time_to_eat / 10);
	}
	return (NULL);
}
