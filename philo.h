/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:51:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/28 19:29:42 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

enum e_definition
{
	TRUE = 1,
	FALSE = -1,
	ERROR = -1
};

typedef struct s_monitoring
{
	pthread_t		*threads;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
	unsigned int	start_time;
	int				number_of_philosophers;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
	int				required_meal_count;
	int				good_death_count;
	int				all_live;
}	t_monitoring;

typedef struct s_philo
{
	pthread_mutex_t	*eat;
	t_monitoring	*moulinette;
    int				id;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				required_meal_count;
	int				current_meal_count;
    int				left_fork;
    int				right_fork;
	int				is_living;
}	t_philo;

#endif