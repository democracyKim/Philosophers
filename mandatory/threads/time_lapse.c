/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_lapse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:37:55 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/30 15:52:37 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	time_lapse(long long time)
{
	struct timeval	start_time;
	struct timeval	current_time;
	long long		elapsed_time;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000LL \
			+ (current_time.tv_usec - start_time.tv_usec) / 1000LL;
		if (elapsed_time >= time)
			break ;
		usleep(1000);
	}
}
