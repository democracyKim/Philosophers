/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:18:46 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 16:52:45 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	start_life_of_philo(t_philo *philo, int i)
{
	philo[i].pid = fork();
	if (philo[i].pid == 0)
	{
		philo->info->start_time = get_time();
		life_of_philo(&philo[i]);
		exit(0);
	}
	else if (philo[i].pid < 0)
	{
		printf("Error: Failed to create process for philosopher %d.\n", i + 1);
		return (ERROR);
	}
	return (0);
}

static int start_odd_philo(t_philo *philo, t_info *info)
{
    int i;

    i = 0;
    while (i < info->number_of_philosophers)
    {
        if (i % 2 == 0)
        {
			if (start_life_of_philo(philo, i) == ERROR)
				return (ERROR);
        }
        i += 2;
    }
    return (0);
}

static int start_even_philo(t_philo *philo, t_info *info)
{
    int i;

    i = 1;
    while (i < info->number_of_philosophers)
    {
        if (i & 1)
        {
			if (start_life_of_philo(philo, i) == ERROR)
				return (ERROR);
        }
        i += 2;
    }
    return (0);
}

int start_philo(t_philo *philo)
{
    t_info *info;

    info = &(philo[0].info);
    if (start_odd_philo(philo, info) == ERROR)
        return (ERROR);
    if (start_even_philo(philo, info) == ERROR)
        return (ERROR);
    return (0);
}