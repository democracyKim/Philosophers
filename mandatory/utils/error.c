/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:42:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 15:43:27 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_error(char *message, t_monitoring *monitoring)
{
	printf("%s\n", message);
	if (monitoring->threads)
		free(monitoring->threads);
	if (monitoring->forks)
		free(monitoring->forks);
	if (monitoring->print)
		free(monitoring->print);
	monitoring->threads = NULL;
	monitoring->forks = NULL;
	monitoring->print = NULL;
	monitoring->error = ERROR;
	return (ERROR);
}

int	is_error(t_monitoring *monitoring)
{
	return (monitoring->error);
}
