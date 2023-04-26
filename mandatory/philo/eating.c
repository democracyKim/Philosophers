/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:10:16 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/26 16:18:38 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	release_forks(t_philo *philo)
{
	if (philo->id & 0)
	{
		pthread_mutex_unlock(&philo->resources->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->resources->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->resources->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->resources->forks[philo->right_fork]);
	}
}

static int take_forks(t_philo *philo)
{
    if (philo->left_fork < philo->right_fork)
    {
        pthread_mutex_lock(&philo->resources->forks[philo->left_fork]);
        pthread_mutex_lock(&philo->resources->forks[philo->right_fork]);
    }
    else
    {
        pthread_mutex_lock(&philo->resources->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->resources->forks[philo->left_fork]);
    }

    if (print_state(philo, "has taken a fork") == ERROR)
        return (ERROR);
    if (print_state(philo, "has taken a fork") == ERROR)
        return (ERROR);

    return (0);
}

// static int	take_forks(t_philo *philo)
// {
// 	if (philo->id & 1)
// 	{
// 		pthread_mutex_lock(&philo->resources->forks[philo->right_fork]);
// 		pthread_mutex_lock(&philo->resources->forks[philo->left_fork]);
// 		if (print_state(philo, "has taken a fork") == ERROR)
// 			return (ERROR);
// 		if (print_state(philo, "has taken a fork") == ERROR)
// 			return (ERROR);
// 	}
// 	else
// 	{
// 		printf("philo->id : %d\n", philo->id);
// 		pthread_mutex_lock(&philo->resources->forks[philo->left_fork]);
// 		pthread_mutex_lock(&philo->resources->forks[philo->right_fork]);
// 		if (print_state(philo, "has taken a fork") == ERROR)
// 			return (ERROR);
// 		if (print_state(philo, "has taken a fork") == ERROR)
// 			return (ERROR);
// 	}
// 	return (0);
// }

static int	start_eating(t_philo *philo)
{
	if (print_state(philo, "is eating") == ERROR)
		return (ERROR);
	time_lapse(philo->info.time_to_eat);
	if (philo->info.must_eat_times != -1)
	{
		pthread_mutex_lock(&philo->resources->stop);
		philo->eat_count++;
		if (philo->eat_count == philo->info.must_eat_times)
		{
			philo->resources->full++;
			philo->fin = 1;
			pthread_mutex_unlock(&philo->resources->stop);
			release_forks(philo);
			return (FULL);
		}
		pthread_mutex_unlock(&philo->resources->stop);
	}
	return (0);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->stop);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->resources->stop);
}

int	eating(t_philo *philo)
{
	int	error;

	error = 0;
	if (take_forks(philo) == ERROR)
		error = 1;
	if (error == 0)
	{
		update_last_meal_time(philo);
		if (start_eating(philo) == FULL)
			return (FULL);
	}
	release_forks(philo);
	return (0);
}
