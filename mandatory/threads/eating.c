/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:05:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/01 21:06:09 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	release_forks(t_philo *philo, t_monitoring *monitoring)
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
		pthread_mutex_lock(monitoring->wait_before_start);
		if (monitoring->all_live == FALSE)
		{
			release_forks(philo, monitoring);
			pthread_mutex_unlock(monitoring->wait_before_start);
			return ;
		}
		pthread_mutex_unlock(monitoring->wait_before_start);
		print_state(philo, "has taken a fork");
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&monitoring->forks[philo->left_fork]);
		pthread_mutex_lock(&monitoring->forks[philo->right_fork]);
		pthread_mutex_lock(monitoring->wait_before_start);
		if (monitoring->all_live == FALSE)
		{
			release_forks(philo, monitoring);
			pthread_mutex_unlock(monitoring->wait_before_start);
			return ;
		}
		print_state(philo, "has taken a fork");
		print_state(philo, "has taken a fork");
		pthread_mutex_unlock(monitoring->wait_before_start);
	}
}

static void	update_last_eat(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(philo->monitoring->wait_before_start);
	pthread_mutex_lock(philo->doing);
	if (philo->monitoring->all_live == FALSE)
	{
		pthread_mutex_unlock(philo->monitoring->wait_before_start);
		pthread_mutex_unlock(philo->doing);
		return ;
	}
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philo->monitoring->wait_before_start);
	philo->last_eat = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	philo->current_meal_count++;
	pthread_mutex_unlock(philo->doing);
}

static int	is_full(t_philo *philo)
{
	pthread_mutex_lock(philo->monitoring->wait_before_start);
	pthread_mutex_lock(philo->doing);
	if (philo->monitoring->required_meal_count == 0 \
		|| philo->current_meal_count != philo->monitoring->required_meal_count)
	{
		pthread_mutex_unlock(philo->monitoring->wait_before_start);
		pthread_mutex_unlock(philo->doing);
		return (FALSE);
	}
	philo->is_living = FALSE;
	philo->monitoring->well_dying++;
	pthread_mutex_unlock(philo->monitoring->wait_before_start);
	pthread_mutex_unlock(philo->doing);
	release_forks(philo, philo->monitoring);
	return (TRUE);
}

int	eating(t_philo *philo)
{
	t_monitoring	*monitoring;

	monitoring = philo->monitoring;
	take_forks(philo, monitoring);
	pthread_mutex_lock(philo->monitoring->wait_before_start);
	if (monitoring->all_live == FALSE)
	{
		release_forks(philo, monitoring);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->monitoring->wait_before_start);
	print_state(philo, "is eating");
	update_last_eat(philo);
	if (is_full(philo) == TRUE)
		return (FALSE);
	time_lapse(philo->time_to_eat);
	release_forks(philo, monitoring);
	return (TRUE);
}
