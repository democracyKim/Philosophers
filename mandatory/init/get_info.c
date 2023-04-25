/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:18:02 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/25 21:09:19 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_integer(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	if (*str == '-')
		return (0);
	while (*str != '\0')
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	get_info(int argc, char *argv[], t_info *info)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (ERROR);
	}
	if (!is_integer(argv[1]) || !is_integer(argv[2]) ||
		!is_integer(argv[3]) || !is_integer(argv[4]) ||
		(argc == 6 && !is_integer(argv[5])))
	{
		printf("Error: Invalid argument values.\n");
		return (ERROR);
	}
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->must_eat_times = ft_atoi(argv[5]);
	else
		info->must_eat_times = -1;
	return (0);
}
