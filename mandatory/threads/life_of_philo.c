/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 15:00:39 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	all_live(t_philo *philo)
{
	pthread_mutex_lock(philo->monitoring->access_monitoring);
	if (philo->monitoring->live_all == FALSE)
	{
		pthread_mutex_unlock(philo->monitoring->access_monitoring);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->monitoring->access_monitoring);
	return (TRUE);
}

static int	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	time_lapse(philo->time_to_sleep);
	if (philo->is_living == FALSE)
		return (FALSE);
	return (TRUE);
}

static void	thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
}

void	life_of_philo(void *arg)
{
	t_monitoring	*monitoring;
	t_philo			*philo;

	
	philo = (t_philo *)arg;
	monitoring = philo->monitoring;
	// pthread_mutex_lock(monitoring->access_monitoring);
	// pthread_mutex_unlock(monitoring->access_monitoring);
	if (philo->id % 2 == 0)
		time_lapse(philo->time_to_eat / 2);
	while (1)
	{
		if (eating(philo) == FALSE)
			break ;
		if (sleeping(philo) == FALSE)
			break ;
		thinking(philo);
		if (all_live(philo) == FALSE)
		{
			return;
		}
	}
}
