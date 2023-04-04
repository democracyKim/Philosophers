/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:08:57 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 16:19:44 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	receive_arguments(t_monitoring *monitoring, t_philo *philo, int i)
{
	philo->monitoring = monitoring;
	philo->id = i + 1;
	philo->time_to_die = monitoring->time_to_die;
	philo->time_to_eat = monitoring->time_to_eat;
	philo->time_to_sleep = monitoring->time_to_sleep;
	philo->left_fork = i;
	philo->right_fork = (i + 1) % monitoring->number_of_philosophers;
	philo->last_meal_time = monitoring->start_time;
	philo->remaining_meal_count = monitoring->required_meal_count;
}

static int	create_mutex(t_philo *philo)
{
	philo->change_last_meal_time = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!philo->change_last_meal_time)
		return (print_error("Error: Memory allocation failed", philo->monitoring));
	philo->change_remaining_meal_count = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!philo->change_remaining_meal_count)
		return (print_error("Error: Memory allocation failed", philo->monitoring));
	return (0);
}

static int	init_mutex(t_philo *philo)
{
	if (pthread_mutex_init(philo->change_last_meal_time, NULL) != 0)
		return (print_error("Error: pthread_mutex_init() failed", philo->monitoring));
	if (pthread_mutex_init(philo->change_remaining_meal_count, NULL) != 0)
		return (print_error("Error: pthread_mutex_init() failed", philo->monitoring));
	return (0);
}

static int	init_philos(t_monitoring *monitoring, t_philo ***philo)
{
	int		i;

	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		(*philo)[i] = ft_calloc(1, sizeof(t_philo));
		if (!(*philo)[i])
		{
			free_philos(philo, i);
			return (print_error("Error: Memory allocation failed", monitoring));
		}
		receive_arguments(monitoring, (*philo)[i], i);
		if (create_mutex((*philo)[i]) == ERROR \
			||init_mutex((*philo)[i]) == ERROR)
		{
			free_philo_mutex(philo, i);
			free_philos(philo, i);
			return (print_error("Error: Memory allocation failed", monitoring));
		}
	}
	return (0);
}

int	init(int argc, char *argv[], t_monitoring **monitoring, t_philo ***philos)
{
	*monitoring = ft_calloc(1, sizeof(t_monitoring));
	if (!*monitoring)
		return (ERROR);
	if (init_minotoring(monitoring, argc, argv) == ERROR)
	{
		free(*monitoring);
		return (ERROR);
	}
	*philos = ft_calloc((*monitoring)->number_of_philosophers, \
		sizeof(t_philo *));
	if (!*philos)
		return (ERROR);
	if (init_philos(*monitoring, philos) == ERROR)
	{
		free(*monitoring);
		return (ERROR);
	}
	return (0);
}
