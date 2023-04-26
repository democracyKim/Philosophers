/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:39:55 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/26 18:13:43 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_philo_dead(t_philo *philo)
{
	unsigned int	current_time;
	unsigned int	time_since_last_meal;

	pthread_mutex_lock(&(philo)->resources->stop);
	current_time = get_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal > philo->info.time_to_die)
	{
		pthread_mutex_unlock(&(philo)->resources->stop);
		return (1);
	}
	pthread_mutex_unlock(&(philo)->resources->stop);
	return (0);
}

static int is_everyone_full(t_philo *philo)
{
	if (philo->info.must_eat_times < 1)
		return (0);
	pthread_mutex_lock(&(philo)->resources->stop);
	if (philo->resources->full == philo->info.number_of_philosophers)
	{
		pthread_mutex_unlock(&(philo)->resources->stop);
		return (1);
	}
	pthread_mutex_unlock(&(philo)->resources->stop);
	return (0);
}

static int	check_philo_state(t_philo *philo)
{
	if (is_philo_dead(philo))
	{
		pthread_mutex_lock(&(philo)->resources->stop);
		if (philo->fin == TRUE)
		{
			pthread_mutex_unlock(&(philo)->resources->stop);
			return (0);
		}
		pthread_mutex_unlock(&(philo)->resources->stop);
		print_state(philo, "died");
		return (FIN);
	}
	if (is_everyone_full(philo))
		return (FIN);
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
				pthread_mutex_lock(&philo[i].resources->stop);
				philo[i].resources->stop_all = TRUE;
				pthread_mutex_unlock(&philo[i].resources->stop);
				pthread_mutex_lock(&philo[i].resources->print);
				return ;
			}
			i++;
		}
	}
	usleep(1000);
}
