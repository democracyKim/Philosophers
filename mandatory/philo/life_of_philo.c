/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:58:36 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 20:00:07 by minkim3          ###   ########.fr       */
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
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		if (eating(philo) != 0)
			return (NULL);
		sleeping(philo);
		thinking(philo);
		usleep(500);
	}
	return (NULL);
}
