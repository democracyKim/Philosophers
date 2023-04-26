/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:58:36 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/26 16:17:42 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int sleeping(t_philo *philo)
{
    if (print_state(philo, "is sleeping") == ERROR)
		return (ERROR);
    time_lapse(philo->info.time_to_sleep);
    return (0);
}

static int thinking(t_philo *philo)
{
    return (print_state(philo, "is thinking"));
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		if (eating(philo) != 0)
			return (NULL);
		if (sleeping(philo) == ERROR)
			return (NULL);
		if (thinking(philo) == ERROR)
			return (NULL);
	}
	return (NULL);
}
