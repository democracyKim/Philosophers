/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:42:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 17:33:22 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
		if ((*philos)[i]->change_last_meal_time)
			free((*philos)[i]->change_last_meal_time);
		(*philos)[i]->change_last_meal_time = NULL;
		if ((*philos)[i]->change_remaining_meal_count)
			free((*philos)[i]->change_remaining_meal_count);
		(*philos)[i]->change_remaining_meal_count = NULL;
	}
}

static void	free_monitoring_thread_and_mutex(t_monitoring **monitoring)
{
	if ((*monitoring)->threads)
		free((*monitoring)->threads);
	if ((*monitoring)->forks)
		free((*monitoring)->forks);
	if ((*monitoring)->change_well_dying)
		free((*monitoring)->change_well_dying);
	if ((*monitoring)->change_starvation)
		free((*monitoring)->change_starvation);
	(*monitoring)->threads = NULL;
	(*monitoring)->forks = NULL;
	(*monitoring)->change_well_dying = NULL;
	(*monitoring)->change_starvation = NULL;

}

int	destroy_mutexes(t_monitoring *monitoring)
{
	int	i;

	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&monitoring->forks[i]) != 0)
			return (print_error("Error: pthread_mutex_destroy() failed", \
				monitoring));
	}
	if (pthread_mutex_destroy(monitoring->change_starvation) != 0)
		return (print_error("Error: pthread_mutex_destroy() failed", monitoring));
	if (pthread_mutex_destroy(monitoring->change_well_dying) != 0)
		return (print_error("Error: pthread_mutex_destroy() failed", monitoring));
	return (0);
}

int	print_error(char *message, t_monitoring *monitoring)
{
	printf("%s\n", message);
	free_monitoring_thread_and_mutex(&monitoring);
	return (ERROR);
}
