/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:24:12 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 14:45:27 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_number_is_plus(t_monitoring *monitoring)
{
	if (monitoring->number_of_philosophers <= 0 \
				|| monitoring->time_to_die <= 0 \
				|| monitoring->time_to_eat <= 0 \
				|| monitoring->time_to_sleep <= 0)
		return (print_error("Error: All args must be positive integers", \
		monitoring));
	else if (monitoring->required_meal_count != 0 && \
		monitoring->required_meal_count <= 0)
		return (print_error("Error: All args must be positive integers", \
			monitoring));
	return (0);
}

static int	create_threads_and_mutex(t_monitoring **monitoring)
{
	(*monitoring)->threads = \
		ft_calloc((*monitoring)->number_of_philosophers, sizeof(pthread_t));
	if (!(*monitoring)->threads)
		return (print_error("Error: Memory allocation failed", *monitoring));
	(*monitoring)->print = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!(*monitoring)->print)
	{
		free((*monitoring)->threads);
		return (print_error("Error: Memory allocation failed", *monitoring));
	}
	(*monitoring)->change_finish = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!(*monitoring)->change_finish)
	{
		free((*monitoring)->threads);
		free((*monitoring)->print);
		return (print_error("Error: Memory allocation failed", *monitoring));
	}
	(*monitoring)->forks = \
		ft_calloc((*monitoring)->number_of_philosophers, \
			sizeof(pthread_mutex_t));
	if (!(*monitoring)->forks)
	{
		free((*monitoring)->threads);
		free((*monitoring)->print);
		free((*monitoring)->change_finish);
		return (print_error("Error: Memory allocation failed", *monitoring));
	}
	return (0);
}

static int	init_mutex(t_monitoring **monitoring)
{
	int	i;

	i = -1;
	if (pthread_mutex_init((*monitoring)->print, NULL))
		return (print_error("Error: Failed to initialize mutex", *monitoring));
	if (pthread_mutex_init((*monitoring)->change_finish, NULL))
		return (print_error("Error: Failed to initialize mutex", *monitoring));
	while (++i < (*monitoring)->number_of_philosophers)
	{
		if (pthread_mutex_init(&((*monitoring)->forks[i]), NULL) != 0)
		{
			return (print_error("Error: Failed to initialize forks", \
			(*monitoring)));
		}
	}
	return (0);
}

static int	get_args(t_monitoring **monitoring, int argc, char *argv[])
{
	(*monitoring)->number_of_philosophers = ft_atoi(argv[1]);
	(*monitoring)->time_to_die = ft_atoi(argv[2]);
	(*monitoring)->time_to_eat = ft_atoi(argv[3]);
	(*monitoring)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*monitoring)->required_meal_count = ft_atoi(argv[5]);
	(*monitoring)->start_time = get_time();
	(*monitoring)->finish = FALSE;
	return (check_number_is_plus(*monitoring));
}

int	init_minotoring(t_monitoring **monitoring, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (print_error("Error: Invalid number of arguments", *monitoring));
	if (get_args(monitoring, argc, argv) == ERROR)
		return (ERROR);
	if (create_threads_and_mutex(monitoring) == ERROR)
		return (ERROR);
	if (init_mutex(monitoring) == ERROR)
		return (ERROR);
	return (0);
}
