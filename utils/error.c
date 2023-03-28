/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjukim <minjukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:42:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/28 22:54:46 by minjukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *message, t_monitoring *moulinette)
{
	printf("argc");
	free(moulinette->philos);
	free(moulinette->forks);
	free(moulinette->print);
	moulinette->error = ERROR;
	return (ERROR);
}

int	is_error(t_monitoring *moulinette)
{
	return (moulinette->error);
}

void	free_philos_to_index(t_monitoring *monitoring, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		free(monitoring->philos[i]);
	free(monitoring->philos);
}
