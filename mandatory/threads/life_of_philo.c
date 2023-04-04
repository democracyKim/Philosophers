/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 11:24:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	stop_thread(t_monitoring *monitoring)
{
	pthread_mutex_lock(monitoring->change_starvation);
	if (monitoring->starvation == TRUE)
	{
		pthread_mutex_unlock(monitoring->change_starvation);
		return (FALSE);
	}
	pthread_mutex_unlock(monitoring->change_starvation);
	// current = get_time();
	// if (current >= philo->last_eat + philo->time_to_die)
	// {
	// 	print_state(philo, "died");
	// 	pthread_mutex_lock(monitoring->change_starvation);
	// 	monitoring->starvation = TRUE;
	// 	pthread_mutex_unlock(monitoring->change_starvation);
	// 	return (FALSE);
	// }
	return (TRUE);
}


static int	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	time_lapse(philo->time_to_sleep);
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
	if (philo->id & 0)
		time_lapse(philo->time_to_eat / 2);
	while (1)
	{
		if (eating(philo) == FALSE)
			break ;
		if (sleeping(philo) == FALSE)
			break ;
		thinking(philo);
		if (stop_thread(monitoring) == FALSE)
			return;
	}
}
