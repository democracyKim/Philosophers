/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:30:35 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/25 17:31:33 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
init
	- get_start_time
	- init resources
	   - create mutexes
	- init philo
		- create thread
*/
int	main(int argc, char *argv[])
{
	t_info		info;
	t_resources	resources;
	t_philo		*philo;

	if (get_info(argc, argv, &info) == ERROR)
		return (1);
	if (init(&info, &resources, &philo) == ERROR)
		return (1);
	// if (start_threads(&philo) == ERROR)
	// 	return (1);
	// while (check_philosopher_status(&philo) == CONTINUE)
	// 	time_lapse(50);
	// close_free(&philo);
	return (0);
}
