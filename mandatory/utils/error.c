/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:42:37 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 15:25:56 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_error(char *message, t_monitoring *monitoring)
{
	printf("%s\n", message);
	free_monitoring_thread_and_mutex(&monitoring);
	return (ERROR);
}
