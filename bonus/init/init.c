/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:06:36 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/10 14:57:55 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int init_resources(t_resources *resources, int number_of_philosophers)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("last_meal");
	sem_unlink("start");
	sem_unlink("prevention");
    resources->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, number_of_philosophers);
	if (resources->forks == SEM_FAILED)
		return (ERROR);
    resources->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
    if (resources->print == SEM_FAILED)
        return (ERROR);
    resources->last_meal = sem_open("last_meal", O_CREAT | O_EXCL, 0644, 1);
    if (resources->last_meal == SEM_FAILED)
        return (ERROR);
	resources->start = sem_open("start", O_CREAT | O_EXCL, 0644, 0);
    if (resources->start == SEM_FAILED)
        return (ERROR);
	resources->prevention = sem_open("prevention", O_CREAT | O_EXCL, 0644, 1);
	if (resources->prevention == SEM_FAILED)
		return (ERROR);
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
        (*philo)[i].info = info;
        (*philo)[i].resources = resources;
        (*philo)[i].id = i + 1;
        (*philo)[i].eat_count = 0;
		(*philo)[i].monitor = (pthread_t *)malloc(sizeof(pthread_t));
		if (!(*philo)[i].monitor)
		{
			free(*philo);
			return (ERROR);
		}
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
    if (init_philosophers(info, resources, philo) == ERROR)
    {
        printf("Error: Failed to initialize philosophers.\n");
        return (ERROR);
    }
    return (0);
}
