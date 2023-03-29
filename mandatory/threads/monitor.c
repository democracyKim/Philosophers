/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 20:33:50 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	monitor(t_monitoring *monitoring)
{
	int	i;

	while (1)
	{
		i = -1;
		if (monitoring->all_live == FALSE)
			return (ERROR);
		if (monitoring->well_dying == monitoring->number_of_philosophers)
			return (ERROR);
		usleep(1000);
	}
	return (0);
}
