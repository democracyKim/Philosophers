/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:01:56 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 13:57:58 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	start_threads(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = -1;
	pthread_mutex_lock(monitoring->access_monitoring);
	while (++i < monitoring->number_of_philosophers)
	{
		if (pthread_create(&monitoring->threads[i], NULL, \
			(void *)life_of_philo, (void *)(philos[i])) != 0)
			return (print_error("Error: pthread_create() failed", monitoring));
	}
	pthread_mutex_unlock(monitoring->access_monitoring);
	return (0);
}

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

static int	destroy_mutexes(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&monitoring->forks[i]) != 0)
			return (print_error("Error: pthread_mutex_destroy() failed", \
				monitoring));
		if (pthread_mutex_destroy(philos[i]->access_philo) != 0)
			return (print_error("Error: pthread_mutex_destroy() failed", \
				monitoring));
	}
	if (pthread_mutex_destroy(monitoring->access_monitoring) != 0)
		return (print_error("Error: pthread_mutex_destroy() failed", \
			monitoring));
	return (0);
}

void	close_free(t_monitoring *monitoring, t_philo **philos)
{
	join_threads(monitoring);
	destroy_mutexes(monitoring, philos);
	free_thread_and_mutex(&monitoring);
	free_philos(&philos, monitoring->number_of_philosophers);
	free(monitoring);
}
