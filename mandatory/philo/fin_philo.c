/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:03:58 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/28 16:10:03 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	join_threads(t_philo **philo)
{
	int		i;
	t_info	*info;

	info = &((*philo)[0].info);
	i = 0;
	while (i < info->number_of_philosophers)
	{
		pthread_join((*philo)[i].threads, NULL);
		i++;
	}
}

static void	destroy_mutexes(t_resources *resources, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&resources->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&resources->print);
	pthread_mutex_destroy(&resources->stop);
}

static void	free_memory(t_philo **philo, t_resources *resources)
{
	free(resources->forks);
	free(*philo);
	*philo = NULL;
}

void	fin_philo(t_philo **philo)
{
	t_info		*info;
	t_resources	*resources;

	info = &((*philo)[0].info);
	resources = (*philo)[0].resources;
	join_threads(philo);
	destroy_mutexes(resources, info->number_of_philosophers);
	free_memory(philo, resources);
}
