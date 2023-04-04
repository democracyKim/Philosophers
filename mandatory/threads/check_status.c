/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 16:00:39 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	is_full(t_philo *philo)
{
	if (philo->monitoring->required_meal_count == 0 || philo->living == FALSE)
		return ;
	pthread_mutex_lock(philo->change_remaining_meal_count);
	pthread_mutex_lock(philo->change_living);
	if (philo->remaining_meal_count == 0)
	{
		pthread_mutex_lock(philo->monitoring->change_well_dying);
		philo->monitoring->well_dying++;
		pthread_mutex_unlock(philo->monitoring->change_well_dying);
		philo->living = FALSE;
	}
	pthread_mutex_unlock(philo->change_living);
	pthread_mutex_unlock(philo->change_remaining_meal_count);
}

static int	is_all_full(t_monitoring *monitoring)
{
	if (monitoring->required_meal_count == 0)
		return (CONTINUE);
	pthread_mutex_lock(monitoring->change_well_dying);
	if (monitoring->well_dying == monitoring->number_of_philosophers)
	{
		pthread_mutex_unlock(monitoring->change_well_dying);
		return (FIN);
	}
	pthread_mutex_unlock(monitoring->change_well_dying);
	return (CONTINUE);
}

static int	is_starving(t_philo *philo, t_monitoring *monitoring)
{
	unsigned int	current;

	pthread_mutex_lock(philo->change_last_meal_time);
	current = get_time();
	if (current >= philo->last_meal_time + philo->time_to_die)
	{
		print_state(philo, "died");
		pthread_mutex_lock(monitoring->change_finish);
		monitoring->finish = TRUE;
		pthread_mutex_unlock(monitoring->change_finish);
		pthread_mutex_unlock(philo->change_last_meal_time);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->change_last_meal_time);
	return (TRUE);
}

int	check_philosopher_status(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		if (is_starving(philos[i], monitoring) == FALSE)
			return (FIN);
		is_full(philos[i]);
		i++;
	}
	if (is_all_full(monitoring) == FIN)
		return (FIN);
	return (CONTINUE);
}
