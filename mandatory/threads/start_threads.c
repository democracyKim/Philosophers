/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:01:56 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 15:32:38 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	start_threads(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		if (pthread_create(&monitoring->threads[i], NULL, \
			(void *)life_of_philo, (void *)(philos[i])) != 0)
			return (print_error("Error: pthread_create() failed", monitoring));
	}
	return (0);
}
