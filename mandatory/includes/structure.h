/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:11:55 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/19 17:47:15 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[1;31m"
# define PINK "\033[1;35m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define DEFAULT "\033[0m"

enum				e_definition
{
	TRUE = 1,
	FALSE = -1,
	ERROR = -1,
	FIN = -1,
	FULL = 1
};

typedef struct s_info
{
	int				number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				must_eat_times;
	unsigned int	start_time;
}					t_info;

typedef struct s_resources
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	*last_meal_time;
	pthread_mutex_t	full;
	pthread_mutex_t	living;
	int				full_count;
	int				live;
	int				*forks_status;
}					t_resources;

typedef struct s_philo
{
	pthread_t		threads;
	t_resources		*resources;
	t_info			info;
	int				id;
	int				left_fork;
	int				right_fork;
	unsigned int	last_meal_time;
	int				eat_count;
}					t_philo;

#endif