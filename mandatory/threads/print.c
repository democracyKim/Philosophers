/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:38:42 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 13:58:24 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_philo *philo, const char *state)
{
	unsigned int	elapsed_time;

	elapsed_time = get_time() - philo->monitoring->start_time;
	pthread_mutex_lock(philo->monitoring->access_monitoring);
	if (philo->monitoring->print_die == FALSE)
		printf("%u %d %s\n", elapsed_time, philo->id, state);
	pthread_mutex_unlock(philo->monitoring->access_monitoring);
}
