/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:51:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 16:48:04 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define RED "\033[1;31m"
# define PINK "\033[1;35m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define DEFAULT "\033[0m"

enum e_definition
{
	TRUE = 1,
	FALSE = -1,
	ERROR = -1,
	FIN = -1,
	CONTINUE = 1
};

typedef struct s_monitoring
{
	pthread_t		*threads;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*change_finish; // if fin = required - 1
	pthread_mutex_t	*change_well_dying;
	unsigned int	start_time;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meal_count;
	int				well_dying;
	int				finish;
}	t_monitoring;

typedef struct s_philo
{
	t_monitoring	*monitoring;
	pthread_mutex_t	*change_meal_info;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				left_fork;
	int				right_fork;
	int				remaining_meal_count;
	unsigned int	last_meal_time;
}	t_philo;

//utils
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
int				print_error(char *message, t_monitoring *monitoring);
void			free_thread_and_mutex(t_monitoring **monitoring);
void			free_philos(t_philo ***philos, int index);
void			free_philo_mutex(t_philo ***philos, int index);
int				destroy_mutexes(t_monitoring *monitoring, t_philo *philos);
int				ft_strcmp(const char *s1, const char *s2);
void			free_monitoring_thread_and_mutex(t_monitoring **monitoring);

//init
int				init(int argc, char *argv[], \
				t_monitoring **monitoring, t_philo ***philos);
int				init_minotoring(t_monitoring **monitoring, int argc, char *argv[]);

//threads
int				start_threads(t_monitoring *monitoring, t_philo **philos);
void			life_of_philo(void *arg);
int				check_philosopher_status(t_monitoring *monitoring, \
				t_philo **philos);
int				eating(t_philo *philo);
void			time_lapse(long long time);
unsigned int	get_time(void);
int				all_live(t_philo *philo);
void			release_forks(t_philo *philo, t_monitoring *monitoring);
void			print_state(t_philo *philo, const char *state);
void			close_free(t_monitoring *monitoring, t_philo **philos);


#endif