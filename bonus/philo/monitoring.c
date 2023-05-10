/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:16:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/10 14:33:50 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int is_philo_dead(t_philo *philo)
{
    unsigned int current_time;
	unsigned int last_meal;
    unsigned int time_since_last_meal;

    current_time = get_time();
	sem_wait(philo->resources->last_meal);
	last_meal = philo->last_meal_time;
	sem_post(philo->resources->last_meal);
    time_since_last_meal = current_time - last_meal;
    if (time_since_last_meal > philo->info->time_to_die)
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
		sem_wait(philo->resources->living);
		philo->resources->live = FALSE;
		sem_post(philo->resources->living);
		return (FIN);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	int		philo_count;
	t_info	*info;
	t_philo *philo;

	philo = (t_philo *)arg;
	info = philo->info;
	philo_count = info->number_of_philosophers;
    while (1)
    {
        if (check_philo_state(philo) == FIN)
		{
			kill_every_philo(philo, philo_count);
            return (NULL);
		}
		usleep(500);
    }
    return (NULL);
}
