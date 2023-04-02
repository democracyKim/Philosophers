/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_lapse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:37:55 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 13:15:46 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	time_lapse(long long time)
{
	struct timeval	start_time;
	struct timeval	current_time;
	unsigned int		elapsed_time;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 \
			+ (current_time.tv_usec - start_time.tv_usec) / 1000;
		if (elapsed_time >= time)
			break ;
		usleep(100);
	}
}

unsigned int	get_time(void)
{
	struct timeval	current_time;
	unsigned int	time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (time);
}
