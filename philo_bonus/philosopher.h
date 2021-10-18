/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:10 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/18 16:38:21 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# define NONE 0
# define ERROR -1
# define SUCCESS 1
# define OPTIONAL_ARG 1
# define MAX_ARGS_NUM 5
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define ONE_MS_IN_US 1000
# define ONE_US_IN_MS 0.001
# define ONE_S_IN_US 1000000

# define BLK "\e[1;90m"
# define RED "\e[1;91m"
# define GRN "\e[1;92m"
# define YEL "\e[1;93m"
# define BLU "\e[1;94m"
# define MAG "\e[1;95m"
# define CYN "\e[1;96m"
# define WHT "\e[1;97m"
# define RST "\e[0m"

typedef enum e_bool {false, true}	t_bool;

typedef enum e_option {set, get}	t_option;

typedef enum e_status_msg {
	taken_fork,
	eating,
	sleeping,
	thinking,
	death
}	t_status_msg;

typedef enum e_is_available {not_available, available}	t_is_available;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_philos;
	int				eating_repeat_time;
	int				philos_eating_time;
	int				total_eating_repeat_time;
	long int		simulation_starting_time;
	int				num_of_philos_completed_eating;
	sem_t			*forks_semaphore;
	sem_t			*main_sem;
	sem_t			*printing_sem;
	sem_t			*eating_time_sem;
	t_bool			repeating_option;
}				t_data;

typedef struct s_philosophers
{
	int				id;
	long int		time_to_die_in_ms;
	sem_t			*death_sem;
}				t_philosophers;

long int	get_curr_time_in_ms(void);
void		*simulation(void *given_philo);
void		*death_thread(void *given_philo);
void		create_eating_count_thread(t_data *data);
void		create_process_per_philosopher(t_data *data);
t_data		*get_data_struct(t_option option, t_data *data_to_set_addr);
void		print_status(int philo_id, t_status_msg msg_id, t_data *data);

#endif
