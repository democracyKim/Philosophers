/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:18:09 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/29 21:22:04 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int print_state(t_philo *philo, const char *statement)
{
    unsigned int philo_time;

    sem_wait(philo->resources->print);
    philo_time = get_time() - philo->info.start_time;
    if (ft_strcmp(statement, "died") == 0)
    {
        printf(RED "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
        return (0);
    }
    else if (ft_strcmp(statement, "is eating") == 0)
        printf(GREEN "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
    else
        printf("%u %d %s\n", philo_time, philo->id, statement);
    sem_post(philo->resources->print);
    return (0);
}
