/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:08:57 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 20:30:18 by minkim3          ###   ########.fr       */
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

static int	parse_arguments(t_monitoring **monitoring, int argc, char *argv[])
{
	struct timeval	tv;

	if (argc < 5 || argc > 6)
		return (print_error("Error: Invalid number of arguments", *monitoring));
	(*monitoring)->number_of_philosophers = ft_atoi(argv[1]);
	(*monitoring)->time_to_die = ft_atoi(argv[2]);
	(*monitoring)->time_to_eat = ft_atoi(argv[3]);
	(*monitoring)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*monitoring)->required_meal_count = ft_atoi(argv[5]);
	(*monitoring)->all_live = TRUE;
	gettimeofday(&tv, NULL);
	(*monitoring)->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (check_number_is_plus(*monitoring));
}

static int	init_resources(t_monitoring **monitoring)
{
	int	i;

	if (is_error(*monitoring) == ERROR)
		return (ERROR);
	(*monitoring)->threads = \
		ft_calloc((*monitoring)->number_of_philosophers, sizeof(pthread_t));
	(*monitoring)->print = \
		ft_calloc(1, sizeof(pthread_mutex_t));
	(*monitoring)->forks = \
		ft_calloc((*monitoring)->number_of_philosophers, sizeof(pthread_mutex_t));
	if (!(*monitoring)->threads || !(*monitoring)->print || !(*monitoring)->forks)
		return (print_error("Error: Memory allocation failed", (*monitoring)));
	if (pthread_mutex_init((*monitoring)->print, NULL) != 0)
		return (print_error("Error: Failed to initialize print_mutex", \
		(*monitoring)));
	i = -1;
	while (++i < (*monitoring)->number_of_philosophers)
		if (pthread_mutex_init(&((*monitoring)->forks[i]), NULL) != 0)
			return (print_error("Error: Failed to initialize forks", \
			(*monitoring)));
	return (0);
}

static int	init_philos(t_monitoring *monitoring, t_philo ***philos)
{
	int		i;

	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		(*philos)[i] = ft_calloc(1, sizeof(t_philo));
		if (!(*philos)[i])
		{
			free_philos(philos, i);
			printf("Error: Memory allocation failed");
			return (ERROR);
		}
		(*philos)[i]->monitoring = monitoring;
		(*philos)[i]->id = i + 1;
		(*philos)[i]->time_to_die = monitoring->time_to_die;
		(*philos)[i]->time_to_eat = monitoring->time_to_eat;
		(*philos)[i]->time_to_sleep = monitoring->time_to_sleep;
		(*philos)[i]->left_fork = i;
		(*philos)[i]->right_fork = (i + 1) % monitoring->number_of_philosophers;
		(*philos)[i]->is_living = TRUE;
	}
	return (0);
}

int	init(int argc, char *argv[], t_monitoring **monitoring, t_philo ***philos)
{
	*monitoring = ft_calloc(1, sizeof(t_monitoring));
	if (!*monitoring)
		return (ERROR);
	parse_arguments(monitoring, argc, argv);
	init_resources(monitoring);
	*philos = ft_calloc((*monitoring)->number_of_philosophers, \
		sizeof(t_philo *));
	if (!*philos)
		return (ERROR);
	if (init_philos(*monitoring, philos) == ERROR)
	{
		free(*monitoring);
		return (ERROR);
	}
	if (is_error(*monitoring) == ERROR)
	{
		free(*monitoring);
		free(*philos);
		return (ERROR);
	}
	return (0);
}