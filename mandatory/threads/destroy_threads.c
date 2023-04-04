/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:25:21 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 16:49:33 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	join_threads(t_monitoring *monitoring)
{
	int	i;

	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		if (pthread_join(monitoring->threads[i], NULL) != 0)
			return (print_error("Error: pthread_join() failed", monitoring));
	}
	return (0);
}

void	free_philos(t_philo ***philos, int index)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		if ((*philos)[i])
			free((*philos)[i]);
		(*philos)[i] = NULL;
	}
	free(*philos);
}

void	free_philo_mutex(t_philo ***philos, int index)
{
	int	i;

	i = -1;
	while(++i < index)
	{
		if ((*philos)[i]->change_meal_info)
			free((*philos)[i]->change_meal_info);
		(*philos)[i]->change_meal_info = NULL;
	}
}

void	free_monitoring_thread_and_mutex(t_monitoring **monitoring)
{
	if ((*monitoring)->threads)
		free((*monitoring)->threads);
	if ((*monitoring)->forks)
		free((*monitoring)->forks);
	if ((*monitoring)->change_finish)
		free((*monitoring)->change_finish);
	if ((*monitoring)->print)
		free((*monitoring)->print);
	if ((*monitoring)->change_well_dying)
		free((*monitoring)->change_well_dying);
	(*monitoring)->threads = NULL;
	(*monitoring)->forks = NULL;
	(*monitoring)->change_finish = NULL;
	(*monitoring)->print = NULL;
	(*monitoring)->change_well_dying = NULL;
}

int	destroy_mutexes(t_monitoring *monitoring, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&monitoring->forks[i]) != 0)
			return (print_error("Error: pthread_mutex_destroy() failed", \
				monitoring));
	}
	if (pthread_mutex_destroy(monitoring->change_finish) != 0)
		return (print_error("Error: pthread_mutex_destroy() failed", monitoring));
	if (pthread_mutex_destroy(monitoring->print) != 0)
		return (print_error("Error: pthread_mutex_destroy() failed", monitoring));
	if (pthread_mutex_destroy(monitoring->change_well_dying) != 0)
		return (print_error("Error: pthread_mutex_destroy() failed", monitoring));
	if (pthread_mutex_destroy(philos->change_meal_info) != 0)
		return (print_error("Error: pthread_mutex_destroy() failed", monitoring));
	return (0);
}

void	close_free(t_monitoring *monitoring, t_philo **philos)
{
	join_threads(monitoring);
	destroy_mutexes(monitoring, *philos);
	free_monitoring_thread_and_mutex(&monitoring);
	free_philo_mutex(&philos, monitoring->number_of_philosophers);
	free_philos(&philos, monitoring->number_of_philosophers);
	free(monitoring);
}
