/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:12:21 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/08 18:31:40 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_mutex(t_resources *resources, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_mutex_init(&resources->forks[i], NULL) != 0)
			return (ERROR);
		i++;
	}
	if (pthread_mutex_init(&resources->print, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&resources->last_meal_time, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&resources->full, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&resources->eat_count, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&resources->living, NULL) != 0)
		return (ERROR);
}

static int	init_resources(t_resources *resources, int number_of_philosophers)
{
	resources->forks = ft_calloc(number_of_philosophers, \
									sizeof(pthread_mutex_t));
	if (!resources->forks)
		return (ERROR);
	init_mutex(resources, number_of_philosophers);
	resources->stop_all_philos = 0;
	resources->full_count = 0;
	return (0);
}

static int	init_philosophers(t_info *info, t_resources *resources,
		t_philo **philo)
{
	int	i;

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

int	init(t_info *info, t_resources *resources, t_philo **philo)
{
	if (init_resources(resources, info->number_of_philosophers) == ERROR)
	{
		printf("Error: Failed to initialize mutexes.\n");
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
