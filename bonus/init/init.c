/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:06:36 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/28 16:07:50 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int init_resources(t_resources *resources, int number_of_philosophers)
{
    int i;

    resources->forks = ft_calloc(number_of_philosophers, sizeof(sem_t));
    if (!resources->forks)
        return (ERROR);
    i = 0;
    while (i < number_of_philosophers)
    {
        if (sem_init(&resources->forks[i], 0, 1) != 0)
            return (ERROR);
        i++;
    }
    if (sem_init(&resources->print, 0, 1) != 0)
        return (ERROR);
    if (sem_init(&resources->stop, 0, 1) != 0)
        return (ERROR);
    resources->stop_all = 0;
    resources->full = 0;
    return (0);
}

static int init_philosophers(t_info *info, t_resources *resources, t_philo **philo)
{
    int i;

    *philo = (t_philo *)malloc(sizeof(t_philo) * info->number_of_philosophers);
    if (!*philo)
        return (ERROR);
    i = 0;
    while (i < info->number_of_philosophers)
    {
        (*philo)[i].info = *info;
        (*philo)[i].resources = resources;
        (*philo)[i].id = i + 1;
        (*philo)[i].left_fork = i;
        (*philo)[i].right_fork = (i + 1) % info->number_of_philosophers;
        (*philo)[i].last_meal_time = get_time();
        (*philo)[i].eat_count = 0;
        i++;
    }
    return (0);
}

int init(t_info *info, t_resources *resources, t_philo **philo)
{
    if (init_resources(resources, info->number_of_philosophers) == ERROR)
    {
        printf("Error: Failed to initialize semaphores.\n");
        return (ERROR);
    }
    info->start_time = get_time();
    if ((int)info->start_time == ERROR)
    {
        printf("Error: Failed to get start time.\n");
        return (ERROR);
    }
    if (init_philosophers(info, resources, philo) == ERROR)
    {
        printf("Error: Failed to initialize philosophers.\n");
        return (ERROR);
    }
    return (0);
}
