/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:15:39 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 16:50:26 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	time_lapse(philo->info.time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
	usleep(500);
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = get_time();
	while (TRUE)
	{
		if (eating(philo) != 0)
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
