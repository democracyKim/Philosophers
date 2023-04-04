/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:05:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 11:17:37 by minkim3          ###   ########.fr       */
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
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->change_last_meal_time);
	if (philo->monitoring->required_meal_count != 0)
	{
		pthread_mutex_lock(philo->change_remaining_meal_count);
		philo->remaining_meal_count--;
		pthread_mutex_unlock(philo->change_remaining_meal_count);
	}
}

static int	is_full(t_philo *philo)
{
	pthread_mutex_lock(philo->change_remaining_meal_count);
	if (philo->remaining_meal_count != 0)
	{
		pthread_mutex_unlock(philo->change_remaining_meal_count);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->change_remaining_meal_count);
	pthread_mutex_lock(philo->monitoring->change_well_dying);
	philo->monitoring->well_dying++;
	pthread_mutex_unlock(philo->monitoring->change_well_dying);
	return (TRUE);
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
	if (philo->is_living == FALSE || is_full(philo) == TRUE)
		return (FALSE);
	return (TRUE);
}
