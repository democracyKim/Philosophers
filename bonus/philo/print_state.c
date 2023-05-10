/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:18:09 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/10 14:58:04 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	print_died(t_philo *philo, unsigned int philo_time, \
		const char *statement)
{
	sem_wait(philo->resources->print);
	printf(RED "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
	sem_post(philo->resources->print);
	return (TRUE);
}

static int	print_eating(t_philo *philo, unsigned int philo_time,
		const char *statement)
{
	sem_wait(philo->resources->print);
	printf(GREEN "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
	sem_post(philo->resources->print);
	return (TRUE);
}

static int	print_statement(t_philo *philo, unsigned int philo_time,
		const char *statement)
{
	sem_wait(philo->resources->print);
	printf("%u %d %s\n", philo_time, philo->id, statement);
	sem_post(philo->resources->print);
	return (TRUE);
}

int	print_state(t_philo *philo, const char *statement)
{
	unsigned int	philo_time;

	philo_time = get_time() - philo->info->start_time;
	if (ft_strcmp(statement, "died") == 0)
	{
		print_died(philo, philo_time, statement);
	}
	else if (ft_strcmp(statement, "is eating") == 0)
	{
		if (print_eating(philo, philo_time, statement) == FALSE)
			return (FIN);
	}
	else
	{
		if (print_statement(philo, philo_time, statement) == FALSE)
			return (FIN);
	}
	return (0);
}
