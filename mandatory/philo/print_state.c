/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:11:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/09 10:36:31 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	should_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->living);
	if (philo->resources->live == FALSE)
	{
		pthread_mutex_unlock(&philo->resources->living);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->resources->living);
	return (TRUE);
}

static void	print_died(t_philo *philo, unsigned int philo_time, \
		const char *statement)
{
	pthread_mutex_lock(&philo->resources->living);
	philo->resources->live = FALSE;
	pthread_mutex_unlock(&philo->resources->living);
	pthread_mutex_lock(&philo->resources->print);
	printf(RED "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
}

static int	print_eating(t_philo *philo, unsigned int philo_time,
		const char *statement)
{
	pthread_mutex_lock(&philo->resources->print);
	if (should_print(philo) == FALSE)
	{
		pthread_mutex_unlock(&philo->resources->print);
		return (FALSE);
	}
	printf(GREEN "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
	return (TRUE);
}

static int	print_statement(t_philo *philo, unsigned int philo_time,
		const char *statement)
{
	pthread_mutex_lock(&philo->resources->print);
	if (should_print(philo) == FALSE)
	{
		pthread_mutex_unlock(&philo->resources->print);
		return (FALSE);
	}
	printf("%u %d %s\n", philo_time, philo->id, statement);
	return (TRUE);
}

int	print_state(t_philo *philo, const char *statement)
{
	unsigned int	philo_time;

	philo_time = get_time() - philo->info.start_time;
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
	pthread_mutex_unlock(&philo->resources->print);
	return (0);
}
