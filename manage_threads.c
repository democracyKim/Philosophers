/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:01:56 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 11:05:04 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_monitoring *monitoring)
{
	int	i;

	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		if (pthread_create(&monitoring->philosophers[i], NULL, \
			life_of_philo, (void *)(&monitoring->philosophers[i]) != 0))
			return (print_error("Error: pthread_create() failed", monitoring));
		i++;
	}
	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		if (pthread_join(monitoring->philosophers[i], NULL) != 0)
			return (print_error("Error: pthread_join() failed", monitoring));
		i++;
	}
}
