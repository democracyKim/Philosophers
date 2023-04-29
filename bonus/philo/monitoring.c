/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:16:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 16:49:53 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_philo_dead(t_philo *philo)
{
	unsigned int	current_time;
	unsigned int	time_since_last_meal;

	sem_wait(philo->resources.stop);
	current_time = get_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal > philo->info.time_to_die)
	{
		sem_post(philo->resources.stop);
		return (1);
	}
	sem_post(philo->resources.stop);
	return (0);
}

static int	check_philo_state(t_philo *philo)
{
	if (is_philo_dead(philo))
	{
		sem_wait(philo->resources.stop);
		sem_post(philo->resources.stop);
		print_state(philo, "died");
		return (FIN);
	}
	return (0);
}

static void kill_every_philo(t_philo *philo, int philo_count)
{
	int j;

	j = 0;
	while(j < philo_count)
	{
		kill(philo[j].pid, SIGTERM);
		j++;
	}
	return ;
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
				kill_every_philo(philo, philo_count);
				return ;
			}
			i++;
		}
	}
	usleep(500);
}
