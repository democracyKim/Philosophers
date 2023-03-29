/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 19:48:47 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	stop_threads(t_philo **philos, t_monitoring *monitoring)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < monitoring->number_of_philosophers)
	{
		philo = philos[i];
		philo->is_living = FALSE;
	}
}

void	monitor(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	while (1)
	{
		i = -1;
		if (monitoring->all_live == FALSE)
			break ;
		if (monitoring->well_dying == monitoring->number_of_philosophers)
			break ;
		usleep(1000);
	}
	stop_threads(philos, monitoring);
}
