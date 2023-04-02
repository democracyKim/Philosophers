/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philosopher_status.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjukim <minjukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 10:47:14 by minjukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_living(t_philo *philo)
{
	struct timeval	current_time;
	unsigned int	time_since_last_eat;

	pthread_mutex_lock(philo->monitoring->wait_before_start);
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philo->doing);
	time_since_last_eat = (current_time.tv_sec * 1000 \
		+ current_time.tv_usec / 1000) - philo->last_eat;
	if (time_since_last_eat >= (unsigned int)philo->time_to_die)
	{
		philo->is_living = FALSE;
		philo->monitoring->all_live = FALSE;
		print_state(philo, "died");
		pthread_mutex_unlock(&philo->monitoring->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->monitoring->forks[philo->right_fork]);
		pthread_mutex_unlock(philo->doing);
		pthread_mutex_unlock(philo->monitoring->wait_before_start);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->doing);
	pthread_mutex_unlock(philo->monitoring->wait_before_start);
	return (TRUE);
}

int	check_philosopher_status(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		pthread_mutex_lock(monitoring->wait_before_start);
		pthread_mutex_lock(philos[i]->doing);
		if (is_living(philos[i]) == FALSE)
		{
			pthread_mutex_unlock(philos[i]->doing);
			pthread_mutex_unlock(monitoring->wait_before_start);
			return (ERROR);
		}
		else if (monitoring->well_dying == monitoring->number_of_philosophers)
		{
			pthread_mutex_unlock(philos[i]->doing);
			pthread_mutex_unlock(monitoring->wait_before_start);
			return (FIN);
		}
		pthread_mutex_unlock(philos[i]->doing);
		pthread_mutex_unlock(monitoring->wait_before_start);
		i++;
	}
	return (0);
}
