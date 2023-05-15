/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:51:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/15 14:41:07 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "structure.h"

int				get_info(int argc, char *argv[], t_info *info);
int				init(t_info *info, t_resources *resources, t_philo **philo);
void			*life_of_philo(t_philo *philo);
int				print_state(t_philo *philo, const char *statement);
int				start_philo(t_philo *philo);
void			*monitoring(void *arg);
void			eating(t_philo *philo);
void			give_usleep(int num);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
int				ft_strcmp(const char *s1, const char *s2);
unsigned int	get_time(void);
void			time_lapse(unsigned int time);
void			fin_philo(t_philo **philo);
void			release_forks(t_philo *philo);
void			kill_every_philo(t_philo *philo, int philo_count);
int				start_life_of_philo(t_philo *philo, int i);
void			free_philo(t_info *info, t_resources *resources, \
					t_philo **philo);

#endif