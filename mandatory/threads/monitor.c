/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 18:56:02 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_philosopher_status(t_philo *philo, t_monitoring *monitoring)
{
	int	well_dying;

	well_dying = 0;
	pthread_mutex_lock(monitoring->print);
	if (!philo->is_living)
	{
		pthread_mutex_unlock(monitoring->print);
		return (ERROR);
	}
	else if (monitoring->required_meal_count > 0 \
			&& philo->current_meal_count >= monitoring->required_meal_count)
		well_dying++;
	pthread_mutex_unlock(monitoring->print);
	return (well_dying);
}

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
	int	well_dying;
	int	i;
	int	status;

	while (1)
	{
		i = -1;
		well_dying = 0;
		while (++i < monitoring->number_of_philosophers)
		{
			status = check_philosopher_status(philos[i], monitoring);
			if (status == -1)
				return ;
			well_dying += status;
		}
		if (well_dying == monitoring->number_of_philosophers)
			break ;
		usleep(1000);
	}
	stop_threads(philos, monitoring);
}
