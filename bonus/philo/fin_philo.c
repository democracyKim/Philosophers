/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:15:03 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 22:36:11 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// static void wait_processes(t_philo **philo)
// {
//     int i;
//     t_info *info;

//     info = &((*philo)[0].info);
//     i = 0;
//     while (i < info->number_of_philosophers)
//     {
//         waitpid((*philo)[i].pid, NULL, 0);
//         i++;
//     }
// }

static void destroy_semaphores(t_resources *resources)
{
    sem_close(resources->forks);
    sem_close(resources->print);
    sem_close(resources->last_meal);
	sem_close(resources->start);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("last_meal");
	sem_unlink("start_sem");
}

static void free_memory(t_philo **philo)
{
	int i;
	
	if (!philo || !*philo)
		return ;
	i = 0;
	while (i < (*philo)->info.number_of_philosophers)
	{
		if ((*philo)[i].monitor)
			free((*philo)[i].monitor);
		i++;
	}
	free(*philo);
    *philo = NULL;
}

static void	join_threads(t_philo *philosophers, int num_philosophers)
{
    for (int i = 0; i < num_philosophers; i++)
    {
        pthread_join(*philosophers[i].monitor, NULL);
    }	
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

void fin_philo(t_philo **philo)
{
    t_info *info;
    t_resources *resources;

    info = &((*philo)[0].info);
    resources = (*philo)[0].resources;
	kill_every_philo(*philo, info->number_of_philosophers);
	join_threads(*philo, info->number_of_philosophers);
	destroy_semaphores(resources);
    free_memory(philo);
}
