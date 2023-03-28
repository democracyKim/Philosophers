/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjukim <minjukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:08:57 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/28 22:52:33 by minjukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_number_is_plus(t_monitoring *monitoring)
{
	if (monitoring->number_of_philosophers <= 0 \
				|| monitoring->time_to_die <= 0 \
				|| monitoring->time_to_eat <= 0 \
				|| monitoring->time_to_sleep <= 0)
		return (print_error("Error: All args must be positive integers", \
		monitoring));
	return (0);
}

static int	parse_arguments(t_monitoring *monitoring, int argc, char *argv[])
{
	struct timeval	tv;

	if (argc < 5 || argc > 6)
		return (print_error("Error: Invalid number of arguments"));
	monitoring->number_of_philosophers = ft_atoi(argv[1]);
	monitoring->time_to_die = ft_atoi(argv[2]);
	monitoring->time_to_eat = ft_atoi(argv[3]);
	monitoring->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		monitoring->required_meal_count = ft_atoi(argv[5]);
		if (monitoring->required_meal_count <= 0)
			return (print_error("Error: All args must be positive integers"));
	}
	monitoring->all_live = TRUE;
	gettimeofday(&tv, NULL);
	monitoring->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (check_number_is_plus(monitoring));
}

static int	init_resources(t_monitoring *monitoring)
{
	int	i;

	if (is_error(monitoring) == ERROR)
		return (ERROR);
	monitoring->philosophers = \
		ft_calloc(monitoring->number_of_philosophers, sizeof(pthread_t));
	monitoring->print = \
		ft_calloc(1, sizeof(pthread_mutex_t));
	monitoring->forks = \
		ft_calloc(monitoring->number_of_philosophers, sizeof(pthread_mutex_t));
	if (!monitoring->philosophers || !monitoring->print || !monitoring->forks)
		return (print_error("Error: Memory allocation failed", monitoring));
	if (pthread_mutex_init(monitoring->print, NULL) != 0)
		return (print_error("Error: Failed to initialize print_mutex", \
		monitoring));
	i = -1;
	while (++i < monitoring->number_of_philosophers)
		if (pthread_mutex_init(&monitoring->forks[i], NULL) != 0)
			return (print_error("Error: Failed to initialize forks", \
			monitoring));
	return (0);
}

static int	init_philosophers(t_monitoring *monitoring)
{
	t_philo	*philo;
	int		i;

	if (is_error(monitoring) == ERROR)
		return (ERROR);
	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		philo = ft_calloc(1, sizeof(t_philo));
		if (!philo)
		{
			free_philos_to_index(monitoring, i);
			return (print_error("Error: Memory allocation failed", monitoring));
		}
		philo->moulinette = monitoring;
		philo->id = i + 1;
		philo->time_to_die = monitoring->time_to_die;
		philo->time_to_eat = monitoring->time_to_eat;
		philo->time_to_sleep = monitoring->time_to_sleep;
		philo->left_fork = i;
		philo->right_fork = (i + 1) % monitoring->number_of_philosophers;
		philo->is_living = TRUE;
		monitoring->philosophers[i] = (pthread_t)philo;
	}
	return (0);
}

t_monitoring	*init(int argc, char *argv[])
{
	t_monitoring	*monitoring;

	monitoring = ft_calloc(1, sizeof(t_monitoring));
	if (!monitoring)
		return (NULL);
	parse_arguments(monitoring, argc, argv);
	init_resources(monitoring);
	init_philosophers(monitoring);
	return (monitoring);
}
