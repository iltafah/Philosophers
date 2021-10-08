/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:01 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/07 16:49:51 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	*death_thread(void *given_philo)
{
	t_philosophers	*curr_philo;

	curr_philo = (t_philosophers *)given_philo;
	while (curr_philo->remaining_time_to_die > 0)
	{
		usleep(1000);
		curr_philo->remaining_time_to_die--;
	}

	struct timeval	time_struct;
	gettimeofday(&time_struct, NULL);
	printf("%ld %d is dead\n", ((time_struct.tv_sec * 1000000 + time_struct.tv_usec)/1000 - data.simulation_starting_time), curr_philo->id);
		
	pthread_mutex_unlock(&data.main_life);
	return (NULL);
}

void	*simulation(void *given_philo)
{
	struct timeval	time_struct;
	int				repated_times;
	t_philosophers	*curr_philo;
	

	repated_times = 0;
	curr_philo = (t_philosophers *)given_philo;
pthread_t death_thread_id;
pthread_create(&death_thread_id, NULL, death_thread, (void*)curr_philo);
	while (repated_times < data.eating_repeat_time)
	{
		gettimeofday(&time_struct, NULL);
			pthread_mutex_lock(&data.forks_mutex[curr_philo->id - 1]);
			printf("%ld %d has taken a fork\n", ((time_struct.tv_sec * 1000000 + time_struct.tv_usec)/1000 - data.simulation_starting_time), curr_philo->id);
			
		gettimeofday(&time_struct, NULL);
			pthread_mutex_lock(&data.forks_mutex[curr_philo->id %  data.num_of_philos]);
			printf("%ld %d has taken a fork\n", ((time_struct.tv_sec * 1000000 + time_struct.tv_usec)/1000 - data.simulation_starting_time), curr_philo->id);
			
			curr_philo->remaining_time_to_die = data.time_to_die + data.time_to_eat;
		gettimeofday(&time_struct, NULL);
			printf("%ld %d is eating\n", ((time_struct.tv_sec * 1000000 + time_struct.tv_usec)/1000 - data.simulation_starting_time), curr_philo->id);
			usleep(data.time_to_eat * 1000);

		pthread_mutex_unlock(&data.forks_mutex[curr_philo->id - 1]);
		pthread_mutex_unlock(&data.forks_mutex[curr_philo->id %  data.num_of_philos]);
	
		curr_philo->remaining_time_to_die = data.time_to_die + data.time_to_sleep;
		gettimeofday(&time_struct, NULL);
		printf("%ld %d is sleeping\n", ((time_struct.tv_sec * 1000000 + time_struct.tv_usec)/1000 - data.simulation_starting_time), curr_philo->id);
		usleep(data.time_to_sleep * 1000);
		
		gettimeofday(&time_struct, NULL);
		printf("%ld %d is thinking\n", ((time_struct.tv_sec * 1000000 + time_struct.tv_usec)/1000 - data.simulation_starting_time), curr_philo->id);
		repated_times++;
	}
	pthread_mutex_unlock(&data.main_life);
	return (NULL);
}

int	convert_arg_to_int(char *argv, int *error)
{
	int			i;
	long int	num;
	
	i = 0;
	num = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
		{
			*error = ERROR;
			return (ERROR);
		}
		num = (num * 10) + (argv[i] - '0');
		i++;
	}
	if (num > MAX_INT)
	{
		*error = ERROR;
		return (ERROR);
	}
	return (num);
}

int	initialize_data(t_data *data, char **argv)
{
	int				error;
	struct timeval	time_struct;

	error = NONE;
	data->num_of_philos = convert_arg_to_int(argv[0], &error);
	data->time_to_die = convert_arg_to_int(argv[1], &error);
	data->time_to_eat = convert_arg_to_int(argv[2], &error);
	data->time_to_sleep = convert_arg_to_int(argv[3], &error);
	if (argv[4] != NULL)
		data->eating_repeat_time = convert_arg_to_int(argv[4], &error);
	else
		data->eating_repeat_time = 0;
	if (error == ERROR)
		return (ERROR);
	// data->forks_availability = malloc(sizeof(t_is_available) * data->num_of_philos);
	data->forks_mutex = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	for (int i = 0; i < data->num_of_philos; i++)
	{
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		// data->forks_availability[i] = available;
	}
	pthread_mutex_init(&data->main_life, NULL);
	gettimeofday(&time_struct, NULL);
	data->simulation_starting_time = (time_struct.tv_sec * 1000000 + time_struct.tv_usec ) / 1000;
	// printf("%ld s\n", time_struct.tv_sec);
	// printf("%ld us\n", time_struct.tv_usec);
	// printf("%ld us\n", (time_struct.tv_sec * 1000000 + time_struct.tv_usec) / 1000);
	// exit(0);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_philosophers	*philo_simulation;
	int					return_code;

    if (argc == MAX_ARGS_NUM || argc == MAX_ARGS_NUM + OPTIONAL_ARG)
    {
		return_code = initialize_data(&data, argv + 1);
		if (return_code == ERROR)
		{
			printf("Error\n");
			return (0);
		}
		//////////
		pthread_t *thread_id = malloc(sizeof(pthread_t) * 5);
		int			*philo_ids = malloc(sizeof(int) * 5);
		for (int id = 0; id < data.num_of_philos; id++)
			philo_ids[id] = id + 1;

		philo_simulation = malloc(sizeof(t_philosophers) * data.num_of_philos);

		int i = 0;
		while (i < data.num_of_philos)
		{
			philo_simulation[i].id = i + 1;
			philo_simulation[i].remaining_time_to_die = data.time_to_die;
			i++;
		}
		
		
		i = 0;
		pthread_mutex_lock(&data.main_life);
		while (i < data.num_of_philos)
		{
			pthread_create(&thread_id[i], NULL, simulation, (void *)&philo_simulation[i]);
			pthread_detach(thread_id[i]);
			usleep(100);
			i++;
		}
		pthread_mutex_lock(&data.main_life);


    }
	else
		printf("Error\n");
    return (0);
}
