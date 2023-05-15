/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:37:46 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/15 14:42:48 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	destroy_semaphores(t_resources *resources)
{
	sem_close(resources->forks);
	sem_close(resources->print);
	sem_close(resources->last_meal);
	sem_close(resources->start);
	sem_close(resources->prevention);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("last_meal");
	sem_unlink("start");
	sem_unlink("prevention");
}

static void	free_memory(t_philo **philo)
{
	int	i;

	if (!philo || !*philo)
		return ;
	i = 0;
	while (i < (*philo)->info->number_of_philosophers)
	{
		if ((*philo)[i].monitor)
			free((*philo)[i].monitor);
		i++;
	}
	free(*philo);
	*philo = NULL;
}

void	free_philo(t_resources *resources, t_philo **philo)
{
	destroy_semaphores(resources);
	free_memory(philo);
}
