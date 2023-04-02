/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:42:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 13:54:44 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_philos(t_philo ***philos, int index)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		if ((*philos)[i]->access_philo)
		{
			free((*philos)[i]->access_philo);
			(*philos)[i]->access_philo = NULL;
		}
		if ((*philos)[i])
			free((*philos)[i]);
		(*philos)[i] = NULL;
	}
	free(*philos);
}

void	free_thread_and_mutex(t_monitoring **monitoring)
{
	if ((*monitoring)->threads)
		free((*monitoring)->threads);
	if ((*monitoring)->forks)
		free((*monitoring)->forks);
	if ((*monitoring)->access_monitoring)
		free((*monitoring)->access_monitoring);
	(*monitoring)->threads = NULL;
	(*monitoring)->forks = NULL;
	(*monitoring)->access_monitoring = NULL;
}

int	print_error(char *message, t_monitoring *monitoring)
{
	printf("%s\n", message);
	free_thread_and_mutex(&monitoring);
	monitoring->error = ERROR;
	return (ERROR);
}

int	is_error(t_monitoring *monitoring)
{
	return (monitoring->error);
}
