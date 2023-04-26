/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:11:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/26 15:47:39 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_philo_state(t_philo *philo)
{
	pthread_mutex_lock(&(philo->resources->stop));
	if (philo->resources->stop_all == TRUE)
	{
		printf("philo->resources->stop_all == %d\n", philo->resources->stop_all);
		pthread_mutex_unlock(&(philo->resources->stop));
		return (ERROR);
	}
	pthread_mutex_unlock(&(philo->resources->stop));
	return (0);
}

int	print_state(t_philo *philo, const char *statement)
{
	unsigned int philo_time;

	pthread_mutex_lock(&philo->resources->print);
	philo_time = get_time() - philo->info.start_time;
	if (ft_strcmp(statement, "died") == 0)
		printf(RED "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
	else if (ft_strcmp(statement, "is eating") == 0)
		printf(GREEN "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
	else if (check_philo_state(philo) == 0)
		printf("%u %d %s\n", philo_time, philo->id, statement);
	pthread_mutex_unlock(&philo->resources->print);
	return (0);
}