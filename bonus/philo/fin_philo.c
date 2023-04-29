/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:15:03 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 16:20:56 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void wait_processes(t_philo **philo)
{
    int i;
    t_info *info;

    info = &((*philo)[0].info);
    i = 0;
    while (i < info->number_of_philosophers)
    {
        waitpid((*philo)[i].pid, NULL, 0);
        i++;
    }
}

static void destroy_semaphores(t_resources *resources)
{
    sem_close(resources->forks);
    sem_close(resources->print);
    sem_close(resources->stop);
}

static void free_memory(t_philo **philo)
{
    free(*philo);
    *philo = NULL;
}

void fin_philo(t_philo **philo)
{
    t_info *info;
    t_resources *resources;

    info = &((*philo)[0].info);
    resources = &(*philo)[0].resources;
	destroy_semaphores(resources);
    wait_processes(philo);
    free_memory(philo);
}
