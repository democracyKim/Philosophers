/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/01 21:02:51 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	time_lapse(philo->time_to_sleep);
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
	pthread_mutex_lock(monitoring->wait_before_start);
	pthread_mutex_unlock(monitoring->wait_before_start);
	if (philo->id % 2 == 0)
		time_lapse(philo->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(monitoring->wait_before_start);
		if (monitoring->all_live == FALSE)
		{
			pthread_mutex_unlock(monitoring->wait_before_start);
			return ;
		}
		if (eating(philo) == FALSE)
			return ;
		pthread_mutex_lock(monitoring->wait_before_start);
		if (monitoring->all_live == FALSE)
		{
			pthread_mutex_unlock(monitoring->wait_before_start);
			return ;
		}
		sleeping(philo);
		pthread_mutex_lock(monitoring->wait_before_start);
		if (monitoring->all_live == FALSE)
		{
			pthread_mutex_unlock(monitoring->wait_before_start);
			return ;
		}
		thinking(philo);
	}
}
