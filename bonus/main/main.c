/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:08:29 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/10 14:42:17 by minkim3          ###   ########.fr       */
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
	if (start_philo(philo) == ERROR)
		return (1);
	fin_philo(&philo);
	return (0);
}