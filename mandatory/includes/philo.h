/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:51:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/25 17:19:59 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "structure.h"

int		get_info(int argc, char *argv[], t_info *info);

int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_strcmp(const char *s1, const char *s2);

#endif