/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:51:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/28 15:53:20 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

enum e_definition
{
	ERROR = -1,
	EQUAL = 0,
	SUCCESS = 0,
};

typedef struct s_args
{
	char	*input_file;
	char	*first_command;
	char	*second_command;
	char	*output_file;
}	t_args;

typedef struct s_pipe
{
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	pid_t	pid_one;
	pid_t	pid_two;
	char	**path;
}	t_pipe;

#endif