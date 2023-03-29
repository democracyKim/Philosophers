/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:51:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 11:05:36 by minkim3          ###   ########.fr       */
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
	pthread_t		*philosophers;
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
	int				error;
}	t_monitoring;

typedef struct s_philo
{
	pthread_mutex_t	*eat;
	t_monitoring	*moulinette;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				current_meal_count;
	int				left_fork;
	int				right_fork;
	int				is_living;
	unsigned int	last_eat;
}	t_philo;

//utils
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
int				print_error(char *message, t_monitoring *moulinette);
int				is_error(t_monitoring *moulinette);
void			free_philos_to_index(t_monitoring *monitoring, int index);
void			print_state(t_philo *philo, const char *state);

//init
t_monitoring	*init(int argc, char *argv[]);

//manage threads
void			start_threads(t_monitoring *monitoring);

#endif