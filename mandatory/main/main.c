/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:30:35 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/26 18:16:36 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_info		info;
	t_resources	resources;
	t_philo		*philo;

	if (get_info(argc, argv, &info) == ERROR)
		return (1);
	if (init(&info, &resources, &philo) == ERROR)
		return (1);
	if (start_threads(philo) == ERROR)
		return (1);
	monitoring(philo);
	// pthread_mutex_unlock(&resources.print);
	fin_philo(&philo);
	return (0);
}
