/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:14:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 16:18:07 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void release_forks(t_philo *philo)
{
	sem_post(philo->resources.forks);
	sem_post(philo->resources.forks);
}

static int take_forks(t_philo *philo)
{
	sem_wait(philo->resources.forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->resources.forks);
	print_state(philo, "has taken a fork");
    return (0);
}

static int start_eating(t_philo *philo)
{
    print_state(philo, "is eating");
    time_lapse(philo->info.time_to_eat);
    if (philo->info.must_eat_times != -1)
    {
        sem_wait(philo->resources.stop);
        philo->eat_count++;
        if (philo->eat_count == philo->info.must_eat_times)
        {
            sem_post(philo->resources.stop);
            release_forks(philo);
            return (FULL);
        }
        sem_post(philo->resources.stop);
    }
    return (0);
}

void update_last_meal_time(t_philo *philo)
{
    sem_wait(philo->resources.stop);
    philo->last_meal_time = get_time();
    sem_post(philo->resources.stop);
}

int eating(t_philo *philo)
{
    int error;

    error = 0;
    if (take_forks(philo) == ERROR)
        error = 1;
    if (error == 0)
    {
        update_last_meal_time(philo);
        if (start_eating(philo) == FULL)
            exit(0);
    }
    release_forks(philo);
    return (0);
}
