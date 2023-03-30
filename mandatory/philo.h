/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjukim <minjukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:51:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/31 02:14:01 by minjukim         ###   ########.fr       */
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
	ERROR = -1,
	FIN = -1
};

typedef struct s_monitoring
{
	pthread_t		*threads;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*wait_before_start;
	unsigned int	start_time;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meal_count;
	int				all_live;
	int				well_dying;
	int				error;
}	t_monitoring;

typedef struct s_philo
{
	pthread_mutex_t	*eat;
	pthread_mutex_t	*status;
	t_monitoring	*monitoring;
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
int				print_error(char *message, t_monitoring *monitoring);
int				is_error(t_monitoring *moulinette);
void			print_state(t_philo *philo, const char *state);
void			free_thread_and_mutex(t_monitoring **monitoring);
void			free_philos(t_philo ***philos, int index);

//init
int				init(int argc, char *argv[], \
				t_monitoring **monitoring, t_philo ***philos);
void			close_free(t_monitoring *monitoring, t_philo **philos);

//threads
int				start_threads(t_monitoring *monitoring, t_philo **philos);
void			life_of_philo(void *arg);
int				check_philosopher_status(t_monitoring *monitoring, \
				t_philo **philos);
int				eating(t_philo *philo);
void			time_lapse(long long time);


#endif