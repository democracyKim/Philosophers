/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:58:36 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/27 12:30:45 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void sleeping(t_philo *philo)
{
    print_state(philo, "is sleeping");
    time_lapse(philo->info.time_to_sleep);
}

static void thinking(t_philo *philo)
{
    print_state(philo, "is thinking");
}

void	give_usleep(int num)
{
	if (num > 1 && num < 5)
		usleep(1);
	else if (num < 20)
		usleep(10);
	else if (num < 30)
		usleep(num);
	else if (num < 100)
		usleep(num * (num / 10));
	else
		usleep(num * (num / 10) + num * (num / 100));

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
		give_usleep(philo->id);
	}
	return (NULL);
}
