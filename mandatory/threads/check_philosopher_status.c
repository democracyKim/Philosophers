/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philosopher_status.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjukim <minjukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/31 02:34:16 by minjukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_living(t_philo *philo)
{
	struct timeval	current_time;
	unsigned int	time_since_last_eat;

	pthread_mutex_lock(philo->monitoring->wait_before_start);
	pthread_mutex_unlock(philo->monitoring->wait_before_start);
	gettimeofday(&current_time, NULL);
	time_since_last_eat = (current_time.tv_sec * 1000 \
		+ current_time.tv_usec / 1000) - philo->last_eat;
	if (time_since_last_eat >= (unsigned int)philo->time_to_die)
	{
		pthread_mutex_lock(philo->status);
		philo->is_living = FALSE;
		philo->monitoring->all_live = FALSE;
		pthread_mutex_unlock(philo->status);
		print_state(philo, "died");
		pthread_mutex_unlock(&philo->monitoring->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->monitoring->forks[philo->right_fork]);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->status);
	return (TRUE);
}

int	check_philosopher_status(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		if (is_living(philos[i]) == FALSE)
			return (ERROR);
		else if (monitoring->well_dying == monitoring->number_of_philosophers)
			return (FIN);
		i++;
	}
	return (0);
}
