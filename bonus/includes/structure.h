
#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define RED "\033[1;31m"
# define PINK "\033[1;35m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define DEFAULT "\033[0m"

enum			e_definition
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
	sem_t			*forks;
	sem_t			*print;
	sem_t			*last_meal;
	sem_t			*start;
	sem_t			*prevention;
}					t_resources;

typedef struct s_philo
{
	pid_t			pid;
	t_resources		*resources;
	pthread_t		*monitor;
	t_info			*info;
	int				id;
	unsigned int	last_meal_time;
	int				eat_count;
}					t_philo;

#endif