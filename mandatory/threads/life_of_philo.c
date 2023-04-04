/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 16:22:59 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_full(t_monitoring *monitoring, t_philo *philo)
{
	if (monitoring->required_meal_count == 0)
		return (FALSE);
	if (philo->remaining_meal_count == 0)
		return (TRUE);
	return (FALSE);
}

int	stop_thread(t_monitoring *monitoring, t_philo *philo)
{
	pthread_mutex_lock(monitoring->change_finish);
	if (monitoring->finish == TRUE)
	{
		pthread_mutex_unlock(monitoring->change_finish);
		return (TRUE);
	}
	pthread_mutex_unlock(monitoring->change_finish);
	if (is_full(monitoring, philo) == TRUE)
		return (TRUE);
	return (FALSE);
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
		if (eating(philo) == FALSE || stop_thread(monitoring, philo) == TRUE)
			return ;
		if (sleeping(philo) == FALSE || stop_thread(monitoring, philo) == TRUE)
			break ;
		if (stop_thread(monitoring, philo) == TRUE)
			return ;
		thinking(philo);
		if (stop_thread(monitoring, philo) == TRUE)
			return ;
	}
}
