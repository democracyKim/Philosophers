/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjukim <minjukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:30:35 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/28 22:56:16 by minjukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_monitoring	*monitoring;

	monitoring = init(argc, argv);
	if (monitoring == NULL || is_error(monitoring) == ERROR)
		return (1);
	
	return (0);
}
