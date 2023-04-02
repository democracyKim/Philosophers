/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 17:24:39 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_living(t_philo *philo)
{
	unsigned int	time_since_last_eat;

	pthread_mutex_lock(philo->access_philo);
	time_since_last_eat = get_time() - philo->last_eat;
	if (time_since_last_eat >= (unsigned int)philo->time_to_die)
	{
		printf("time_since_last_eat: %u\n", time_since_last_eat);
		printf("philo->time_to_die: %d\n", philo->time_to_die);
		printf("philo->id: %d\n", philo->id);
		philo->is_living = FALSE;
		printf("ok1\n");
		pthread_mutex_lock(philo->monitoring->access_monitoring);
		printf("ok2\n");
		philo->monitoring->live_all = FALSE;
		print_state(philo, "died");
		philo->monitoring->print_die = TRUE;
		pthread_mutex_unlock(philo->monitoring->access_monitoring);
		pthread_mutex_unlock(philo->access_philo);
		release_forks(philo, philo->monitoring);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->access_philo);
	return (TRUE);
}

int	check_philosopher_status(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		pthread_mutex_lock(monitoring->access_monitoring);
		if (is_living(philos[i]) == FALSE)
		{
			pthread_mutex_unlock(monitoring->access_monitoring);
			return (ERROR);
		}
		else if (monitoring->well_dying == monitoring->number_of_philosophers)
		{
			pthread_mutex_unlock(monitoring->access_monitoring);
			return (FIN);
		}
		pthread_mutex_unlock(monitoring->access_monitoring);
		i++;
	}
	return (0);
}
