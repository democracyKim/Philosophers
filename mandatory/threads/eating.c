/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:05:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 15:56:45 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	release_forks(t_philo *philo, t_monitoring *monitoring)
{
	if (philo->id & 0)
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
	if (philo->id & 0)
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
	pthread_mutex_lock(philo->change_last_meal_time);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->change_last_meal_time);
	pthread_mutex_lock(philo->change_remaining_meal_count);
	if (philo->remaining_meal_count != 0)
		philo->remaining_meal_count--;
	pthread_mutex_unlock(philo->change_remaining_meal_count);
}

int	eating(t_philo *philo)
{
	t_monitoring	*monitoring;

	monitoring = philo->monitoring;
	take_forks(philo, monitoring);
	print_state(philo, "is eating");
	time_lapse(philo->time_to_eat);
	update_last_eat(philo);
	release_forks(philo, monitoring);
	return (TRUE);
}
