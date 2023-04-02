/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:05:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 15:27:59 by minkim3          ###   ########.fr       */
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
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philo->access_philo);
	philo->last_eat = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	philo->current_meal_count++;
	pthread_mutex_unlock(philo->access_philo);
}

static int	is_full(t_philo *philo)
{
	if (philo->monitoring->required_meal_count == 0 \
		|| philo->current_meal_count != philo->monitoring->required_meal_count)
	{
		return (FALSE);
	}
	philo->is_living = FALSE;
	philo->monitoring->well_dying++;
	pthread_mutex_lock(philo->monitoring->access_monitoring);
	philo->monitoring->live_all = FALSE;
	pthread_mutex_unlock(philo->monitoring->access_monitoring);
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
