/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:12:21 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/25 20:38:51 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_mutexes(t_resources *resources, int number_of_philosophers)
{
	int	i;

	resources->forks = ft_calloc(number_of_philosophers, \
			sizeof(pthread_mutex_t));
	if (!resources->forks)
		return (ERROR);
	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_mutex_init(&resources->forks[i], NULL) != 0)
			return (ERROR);
		i++;
	}
	if (pthread_mutex_init(&resources->print, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&resources->stop, NULL) != 0)
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
		(*philo)[i].info = *info;
		(*philo)[i].resources = resources;
		(*philo)[i].id = i + 1;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % info->number_of_philosophers;
		(*philo)[i].last_meal_time = 0;
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}

int init(t_info *info, t_resources *resources, t_philo **philo)
{
	info->start_time = get_time();
	if (info->start_time == ERROR)
	{
		printf("Error: Failed to get start time.\n");
		return (ERROR);
	}
	if (init_mutexes(resources, info->number_of_philosophers) == ERROR)
	{
		printf("Error: Failed to initialize mutexes.\n");
		return (ERROR);
	}
	if (init_philosophers(info, resources, philo) == ERROR)
	{
		printf("Error: Failed to initialize philosophers.\n");
		return (ERROR);
	}
	return (0);
}