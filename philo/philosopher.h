/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:10 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/14 15:45:13 by iltafah          ###   ########.fr       */
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
# define one_ms_in_us 1000
# define one_us_in_ms 0.001
# define one_s_in_us 1000000

#define BLK "\e[1;90m"
#define RED "\e[1;91m"
#define GRN "\e[1;92m"
#define YEL "\e[1;93m"
#define BLU "\e[1;94m"
#define MAG "\e[1;95m"
#define CYN "\e[1;96m"
#define WHT "\e[1;97m"
#define reset "\e[0m"

typedef enum e_bool {false, true} t_bool;

typedef enum e_status_msg {taken_fork, eating, sleeping, thinking, death} t_status_msg;

typedef enum e_is_available {not_available, available} t_is_available;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_philos;
	int				eating_repeat_time;
	long int		simulation_starting_time;
	pthread_mutex_t main_mutex;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	printing_mutex;
	t_bool			repeating_option;
}				t_data;

typedef struct s_philosophers
{
	int				id;
	long int		time_to_die_in_ms;
	pthread_mutex_t	death_mutex;
}				t_philosophers;

static t_data	data;

#endif
