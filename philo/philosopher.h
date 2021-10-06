/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:10 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/06 17:13:51 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define NONE 0
# define ERROR -1
# define SUCCESS 1
# define OPTIONAL_ARG 1
# define MAX_ARGS_NUM 5
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_philo_vars
{
	int		time_to_die;
	int		time_to_eat;
	int		num_of_philos;
	int		time_to_sleep;
	int		eating_repeat_time;
}				t_philo_vars;

#endif
