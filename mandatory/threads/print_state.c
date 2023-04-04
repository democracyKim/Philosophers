/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:38:42 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 15:23:58 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_philo *philo, const char *state)
{
    unsigned int elapsed_time;

    elapsed_time = get_time() - philo->monitoring->start_time;
    pthread_mutex_lock(philo->monitoring->print);
	pthread_mutex_lock(philo->monitoring->change_finish);
	if (philo->monitoring->finish == FALSE)
    {
		pthread_mutex_unlock(philo->monitoring->change_finish);
        if (ft_strcmp(state, "died") == 0)
        {
			pthread_mutex_lock(philo->monitoring->change_finish);
			philo->monitoring->finish = TRUE;
			pthread_mutex_unlock(philo->monitoring->change_finish);
            printf(RED "%u %d %s" DEFAULT "\n", elapsed_time, philo->id, state);
        }
        if (ft_strcmp(state, "is eating") == 0)
            printf(GREEN "%u %d %s" DEFAULT "\n", elapsed_time, philo->id, state);
        else
            printf("%u %d %s\n", elapsed_time, philo->id, state);
    }
    pthread_mutex_unlock(philo->monitoring->print);
}
