/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:16:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 19:51:10 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int is_philo_dead(t_philo *philo)
{
    unsigned int current_time;
    unsigned int time_since_last_meal;

    sem_wait(philo->resources.stop);
    current_time = get_time();
    time_since_last_meal = current_time - philo->last_meal_time;
    sem_post(philo->resources.stop);
    if (time_since_last_meal > philo->info.time_to_die)
    {
        return (1);
    }
    return (0);
}


static int	check_philo_state(t_philo *philo)
{
	if (is_philo_dead(philo))
	{
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

void	*monitoring(void *arg)
{
	int		philo_count;
	t_info	*info;
	t_philo *philo;

	philo = (t_philo *)arg;
	info = &(philo->info);
	philo_count = info->number_of_philosophers;
	while (1)
	{
		usleep(500);
		if (check_philo_state(philo) == FIN)
		{
			kill_every_philo(philo, philo_count);
			exit(1);
		}
	}
	return (NULL);
}
