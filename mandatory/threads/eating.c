/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:05:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/30 11:19:53 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	take_forks(t_philo *philo, t_monitoring *monitoring)
{
	if (philo->id % 2)
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
}

static void	update_last_eat(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	philo->last_eat = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	philo->current_meal_count++;
}

static int	is_full(t_philo *philo)
{
	if (philo->monitoring->required_meal_count == 0 \
		|| philo->current_meal_count == philo->monitoring->required_meal_count)
		return (FALSE);
	philo->is_living = FALSE;
	philo->monitoring->well_dying++;
	// print_state(philo, "died");
	pthread_mutex_unlock(&philo->monitoring->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->monitoring->forks[philo->right_fork]);
	return (TRUE);
}

int	eating(t_philo *philo)
{
	t_monitoring	*monitoring;

	monitoring = philo->monitoring;
	take_forks(philo, monitoring);
	print_state(philo, "is eating");
	update_last_eat(philo);
	if (is_full(philo) == TRUE)
		return (FALSE);
	usleep(monitoring->time_to_eat * 1000);
	pthread_mutex_unlock(&monitoring->forks[philo->left_fork]);
	pthread_mutex_unlock(&monitoring->forks[philo->right_fork]);
	return (is_living(philo));
}