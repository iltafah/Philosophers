/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:10 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/07 15:49:41 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define NONE 0
# define ERROR -1
# define SUCCESS 1
# define OPTIONAL_ARG 1
# define MAX_ARGS_NUM 5
# define MAX_INT 2147483647
# define MIN_INT -2147483648

enum e_bool {false, true};

typedef enum e_is_available {not_available, available} t_is_available;

typedef struct s_philo_vars
{
	int				time_to_die;
	int				time_to_eat;
	int				num_of_philos;
	int				time_to_sleep;
	int				eating_repeat_time;
	int				simulation_starting_time;
	// t_is_available	*forks_availability;
	pthread_mutex_t	*forks_mutex;
}				t_philo_vars;

typedef struct s_philosophers
{
	int				id;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	t_is_available	is_fork_available;
	t_is_available	*next_fork_ptr;
}				t_philosophers;

static t_philo_vars	philo_vars;

#endif
