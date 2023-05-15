/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:15:03 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/15 14:43:08 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	wait_processes(t_philo **philo)
{
	int		i;
	t_info	*info;
	int		status;

	info = philo[0]->info;
	i = 0;
	while (i < info->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			return ;
		}
		i++;
	}
}

static void	join_threads(t_philo *philosophers, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_join(*philosophers[i].monitor, NULL);
		i++;
	}
}

void	kill_every_philo(t_philo *philo, int philo_count)
{
	int	j;

	j = 0;
	while (j < philo_count)
	{
		kill(philo[j].pid, SIGTERM);
		j++;
	}
	return ;
}

void	fin_philo(t_philo **philo)
{
	t_info		*info;
	t_resources	*resources;

	info = philo[0]->info;
	resources = (*philo)[0].resources;
	join_threads(*philo, info->number_of_philosophers);
	wait_processes(philo);
	kill_every_philo(*philo, info->number_of_philosophers);
	free_philo(resources, philo);
}
