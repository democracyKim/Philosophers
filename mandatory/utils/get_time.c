/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:34:12 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/25 19:30:32 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	time_lapse(int time)
{
	unsigned int	start_time;
	unsigned int	current_time;
	unsigned int	elapsed_time;

	start_time = get_time();
	while (TRUE)
	{
		current_time = get_time();
		elapsed_time = current_time - start_time;
		if (elapsed_time >= (unsigned int)time)
			break ;
		usleep(1000);
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
