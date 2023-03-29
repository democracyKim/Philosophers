/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 11:49:50 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_living(t_philo *philo)
{
	struct timeval	current_time;
	unsigned int	time_since_last_eat;

	gettimeofday(&current_time, NULL);
	time_since_last_eat = (current_time.tv_sec * 1000 \
		+ current_time.tv_usec / 1000) - philo->last_eat;
	if (time_since_last_eat >= philo->time_to_die)
	{
		philo->is_living = FALSE;
		print_state(philo, "died");
		return (FALSE);
	}
	return (TRUE);
}

static int	eating(t_philo *philo)
{
	struct timeval	current_time;
	t_monitoring	*monitoring;

	monitoring = philo->moulinette;
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&monitoring->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&monitoring->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&monitoring->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&monitoring->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
	}
	print_state(philo, "is eating");
	gettimeofday(&current_time, NULL);
	philo->last_eat = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	usleep(monitoring->time_to_eat * 1000);
	pthread_mutex_unlock(&monitoring->forks[philo->left_fork]);
	pthread_mutex_unlock(&monitoring->forks[philo->right_fork]);
	return (is_living(philo));
}

static int	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
	return(is_living(philo));
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
	while (1)
	{
		if (eating(philo) == FALSE)
			break ;
		if (sleeping(philo) == FALSE)
			break ;
		if (thinking(philo) == FALSE)
			break ;
	}
}
