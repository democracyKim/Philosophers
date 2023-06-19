/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:39:55 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/19 17:50:07 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_philo_dead(t_philo *philo, int id)
{
	unsigned int	current_time;
	unsigned int	time_since_last_meal;

	current_time = get_time();
	pthread_mutex_lock(&(philo)->resources->last_meal_time[id]);
	time_since_last_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&(philo)->resources->last_meal_time[id]);
	if (time_since_last_meal > philo->info.time_to_die)
		return (1);
	return (0);
}

static int	is_everyone_full(t_philo *philo)
{
	if (philo->info.must_eat_times < 1)
		return (0);
	pthread_mutex_lock(&(philo)->resources->full);
	if (philo->resources->full_count == philo->info.number_of_philosophers)
	{
		pthread_mutex_unlock(&(philo)->resources->full);
		return (1);
	}
	pthread_mutex_unlock(&(philo)->resources->full);
	return (0);
}

static int	check_philo_state(t_philo *philo)
{
	if (is_everyone_full(philo))
		return (FIN);
	if (is_philo_dead(philo, philo->id))
	{
		print_state(philo, "died");
		return (FIN);
	}
	return (0);
}

void	monitoring(t_philo *philo)
{
	int		i;
	int		philo_count;
	t_info	*info;

	info = &(philo[0].info);
	philo_count = info->number_of_philosophers;
	while (1)
	{
		i = 0;
		while (i < philo_count)
		{
			if (check_philo_state(&philo[i]) == FIN)
			{
				return ;
			}
			i++;
		}
		usleep(500);
	}
}
