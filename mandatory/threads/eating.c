/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:05:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 13:37:29 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	release_forks(t_philo *philo, t_monitoring *monitoring)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&monitoring->forks[philo->right_fork]);
		pthread_mutex_unlock(&monitoring->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&monitoring->forks[philo->left_fork]);
		pthread_mutex_unlock(&monitoring->forks[philo->right_fork]);
	}
}

static void	take_forks(t_philo *philo, t_monitoring *monitoring)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&monitoring->forks[philo->right_fork]);
		pthread_mutex_lock(&monitoring->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&monitoring->forks[philo->left_fork]);
		pthread_mutex_lock(&monitoring->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
		print_state(philo, "has taken a fork");
	}
}

static void	update_last_eat(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	philo->last_eat = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	philo->current_meal_count++;
}

int	eating(t_philo *philo)
{
	t_monitoring	*monitoring;

	monitoring = philo->monitoring;
	take_forks(philo, monitoring);
	print_state(philo, "is eating");
	update_last_eat(philo);
	time_lapse(philo->time_to_eat);
	release_forks(philo, monitoring);
	if (philo->is_living == FALSE)
		return (FALSE);
	return (TRUE);
}
