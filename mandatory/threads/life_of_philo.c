/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjukim <minjukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 10:57:53 by minjukim         ###   ########.fr       */
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
	while (philo->is_living)
	{
		if (is_living(philo) == FALSE)
			return ;
		if (eating(philo) == FALSE)
			return ;
		if (is_living(philo) == FALSE)
			return ;
		sleeping(philo);
		if (is_living(philo) == FALSE)
			return ;
		thinking(philo);
		if (is_living(philo) == FALSE)
			return ;
	}
}
