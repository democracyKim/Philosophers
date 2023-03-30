/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/30 14:34:18 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_living(t_philo *philo)
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
		philo->is_living = FALSE;
		philo->monitoring->all_live = FALSE;
		print_state(philo, "died");
		pthread_mutex_unlock(&philo->monitoring->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->monitoring->forks[philo->right_fork]);
		return (FALSE);
	}
	return (TRUE);
}

static int	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
	return (is_living(philo));
}

static int	thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
	return (is_living(philo));
}

void	life_of_philo(void *arg)
{
	t_monitoring	*monitoring;
	t_philo			*philo;

	philo = (t_philo *)arg;
	monitoring = philo->monitoring;
	while (monitoring->all_live)
	{
		if (eating(philo) == FALSE || monitor(monitoring) == ERROR)
			return ;
		if (sleeping(philo) == FALSE || monitor(monitoring) == ERROR)
			return ;
		if (thinking(philo) == FALSE || monitor(monitoring) == ERROR)
			return ;
	}
}
