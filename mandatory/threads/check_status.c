/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 16:50:15 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	is_full(t_philo *philo, t_monitoring *monitoring)
{
	if (monitoring->required_meal_count == 0)
		return ;
	pthread_mutex_lock(philo->change_meal_info);
	if (philo->remaining_meal_count == 0)
	{
		pthread_mutex_unlock(philo->change_meal_info);
		pthread_mutex_lock(monitoring->change_well_dying);
		monitoring->well_dying++;
		pthread_mutex_unlock(monitoring->change_well_dying);
		pthread_mutex_lock(monitoring->change_finish);
		monitoring->finish = TRUE;
		pthread_mutex_unlock(monitoring->change_finish);
	}
	pthread_mutex_unlock(philo->change_meal_info);
	return ;
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

	pthread_mutex_lock(philo->change_meal_info);
	current = get_time();
	if (current >= philo->last_meal_time + philo->time_to_die)
	{
		pthread_mutex_unlock(philo->change_meal_info);
		print_state(philo, "died");
		pthread_mutex_lock(monitoring->change_finish);
		monitoring->finish = TRUE;
		pthread_mutex_unlock(monitoring->change_finish);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->change_meal_info);
	return (TRUE);
}

static int	is_fin(t_monitoring *monitoring)
{
	pthread_mutex_lock(monitoring->change_finish);
	if (monitoring->finish == TRUE)
	{
		pthread_mutex_unlock(monitoring->change_finish);
		return (TRUE);
	}
	pthread_mutex_unlock(monitoring->change_finish);
	return (FALSE);
}

int	check_philosopher_status(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		if (is_starving(philos[i], monitoring) == FALSE)
			return (FIN);
		is_full(philos[i], monitoring);
		i++;
		if (is_fin(monitoring) == TRUE)
			return (FIN);
	}
	if (is_all_full(monitoring) == FIN)
		return (FIN);
	return (CONTINUE);
}
