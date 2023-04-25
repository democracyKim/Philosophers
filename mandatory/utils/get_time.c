/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:34:12 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/25 17:34:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned int	get_time(void)
{
	struct timeval	current_time;
	unsigned int	time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (time);
}
