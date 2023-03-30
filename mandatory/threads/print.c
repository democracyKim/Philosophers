/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:38:42 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/30 13:33:50 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_philo *philo, const char *state)
{
	struct timeval	current_time;
	unsigned int	elapsed_time;

	pthread_mutex_lock(philo->monitoring->print);
	gettimeofday(&current_time, NULL);
	elapsed_time = current_time.tv_sec * 1000 + \
		current_time.tv_usec / 1000 - philo->monitoring->start_time;
	printf("%u %d %s\n", elapsed_time, philo->id, state);
	pthread_mutex_unlock(philo->monitoring->print);
}