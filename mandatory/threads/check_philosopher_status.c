/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philosopher_status.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 13:42:27 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_full(t_philo *philo)
{
	if (philo->monitoring->required_meal_count == 0 \
		|| philo->current_meal_count != philo->monitoring->required_meal_count)
	{
		return (FALSE);
	}
	philo->is_living = FALSE;
	philo->monitoring->well_dying++;
	release_forks(philo, philo->monitoring);
	return (TRUE);
}

static int	is_living(t_philo *philo)
{
	unsigned int	time_since_last_eat;

	time_since_last_eat = get_time() - philo->last_eat;
	printf("time_since_last_eat: %u\n", time_since_last_eat);
	if (time_since_last_eat >= (unsigned int)philo->time_to_die)
	{
		philo->is_living = FALSE;
		philo->monitoring->live_all = FALSE;
		print_state(philo, "died");
		philo->monitoring->print_die = TRUE;
		release_forks(philo, philo->monitoring);
		return (FALSE);
	}
	return (TRUE);
}

int	check_philosopher_status(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		pthread_mutex_lock(monitoring->wait_before_start);
		is_full(philos[i]);
		if (is_living(philos[i]) == FALSE)
		{
			pthread_mutex_unlock(monitoring->wait_before_start);
			return (ERROR);
		}
		else if (monitoring->well_dying == monitoring->number_of_philosophers)
		{
			pthread_mutex_unlock(monitoring->wait_before_start);
			return (FIN);
		}
		pthread_mutex_unlock(monitoring->wait_before_start);
		i++;
	}
	return (0);
}
