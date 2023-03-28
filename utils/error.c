/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjukim <minjukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:42:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/28 23:11:38 by minjukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *message, t_monitoring *moulinette)
{
	printf("%s\n", message);
	free_philos_to_index(moulinette, moulinette->number_of_philosophers);
	if (moulinette->philosophers)
		free(moulinette->philosophers);
	if (moulinette->forks)
		free(moulinette->forks);
	if (moulinette->print)
		free(moulinette->print);
	moulinette->philosophers = NULL;
	moulinette->forks = NULL;
	moulinette->print = NULL;
	moulinette->error = ERROR;
	return (ERROR);
}

int	is_error(t_monitoring *moulinette)
{
	return (moulinette->error);
}

void	free_philos_to_index(t_monitoring *moulinette, int index)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		if (moulinette->philosophers[i] != NULL)
			free(moulinette->philosophers[i]);
		moulinette->philosophers[i] = NULL;
	}
}
