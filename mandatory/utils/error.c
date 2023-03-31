/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:42:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/31 16:57:08 by minkim3          ###   ########.fr       */
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

void	free_thread_and_mutex(t_monitoring **monitoring)
{
	if ((*monitoring)->threads)
		free((*monitoring)->threads);
	if ((*monitoring)->forks)
		free((*monitoring)->forks);
	if ((*monitoring)->print)
		free((*monitoring)->print);
	if ((*monitoring)->wait_before_start)
		free((*monitoring)->wait_before_start);
	(*monitoring)->threads = NULL;
	(*monitoring)->forks = NULL;
	(*monitoring)->print = NULL;
	(*monitoring)->wait_before_start = NULL;
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
