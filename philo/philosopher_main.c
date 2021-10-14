/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:01 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/14 15:45:01 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

long int	get_curr_time_in_ms(void)
{
	struct timeval	time_struct;
	long int		curr_time_in_ms;

	gettimeofday(&time_struct, NULL);
	curr_time_in_ms = (time_struct.tv_sec * one_s_in_us + time_struct.tv_usec) * one_us_in_ms;
	return (curr_time_in_ms);
}

void	print_status(int philo_id, t_status_msg msg_id)
{
	long int		curr_time_in_ms;
	long int		simulation_curr_time_ms;
	static char		colors[5][8] = {WHT, GRN, CYN, YEL, RED};
	static char		messages[5][20] = 
	{
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"is died"
	};

	pthread_mutex_lock(&data.printing_mutex);
	curr_time_in_ms = get_curr_time_in_ms();
	simulation_curr_time_ms = curr_time_in_ms - data.simulation_starting_time;
	printf("%s", WHT);
	printf("%ld\t%d", simulation_curr_time_ms, philo_id);
	printf("\t%s%s%s\n", colors[msg_id], messages[msg_id], reset);
	if (msg_id == death)
		return ;
	pthread_mutex_unlock(&data.printing_mutex);
}

void	*death_thread(void *given_philo)
{
	t_philosophers	*curr_philo;

	curr_philo = (t_philosophers *)given_philo;
	curr_philo->time_to_die_in_ms = get_curr_time_in_ms() + data.time_to_die;
	while (true)
	{
		pthread_mutex_lock(&curr_philo->death_mutex);
		if (get_curr_time_in_ms() > curr_philo->time_to_die_in_ms)
			break ;
		pthread_mutex_unlock(&curr_philo->death_mutex);
		usleep(500);
	}
	print_status(curr_philo->id, death);		
	pthread_mutex_unlock(&data.main_mutex);
	return (NULL);
}

void	pick_up_forks(int philo_id)
{
	pthread_mutex_lock(&data.forks_mutex[philo_id - 1]);
	print_status(philo_id, taken_fork);
	pthread_mutex_lock(&data.forks_mutex[philo_id %  data.num_of_philos]);
	print_status(philo_id, taken_fork);
}

void	drop_forks(int philo_id)
{
	pthread_mutex_unlock(&data.forks_mutex[philo_id - 1]);
	pthread_mutex_unlock(&data.forks_mutex[philo_id %  data.num_of_philos]);
}

void	eat_spaghetti(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	print_status(philo->id, eating);
	usleep(data.time_to_eat * one_ms_in_us);
	drop_forks(philo->id);
	philo->time_to_die_in_ms = get_curr_time_in_ms() + data.time_to_die - data.time_to_eat;
	pthread_mutex_unlock(&philo->death_mutex);
}

void	sleeping_time(int philo_id)
{
	print_status(philo_id, sleeping);
	usleep(data.time_to_sleep * one_ms_in_us);
}

void	*simulation(void *given_philo)
{
	int				repated_times;
	pthread_t		death_thread_id;
	t_philosophers	*curr_philo;	

	repated_times = 0;
	curr_philo = (t_philosophers *)given_philo;
	pthread_create(&death_thread_id, NULL, death_thread, (void*)curr_philo);
	pthread_detach(death_thread_id);
	while (true)
	{
		if (data.repeating_option == true && ++repated_times > data.eating_repeat_time)
			break ;
		pick_up_forks(curr_philo->id);
		eat_spaghetti(curr_philo);
		sleeping_time(curr_philo->id);
		print_status(curr_philo->id, thinking);
	}
	pthread_mutex_unlock(&data.main_mutex);
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

	error = NONE;
	data->num_of_philos = convert_arg_to_int(argv[0], &error);
	data->time_to_die = convert_arg_to_int(argv[1], &error);
	data->time_to_eat = convert_arg_to_int(argv[2], &error);
	data->time_to_sleep = convert_arg_to_int(argv[3], &error);
	if (argv[4] != NULL)
	{
		data->repeating_option = true;
		data->eating_repeat_time = convert_arg_to_int(argv[4], &error);
	}
	else
	{
		data->repeating_option = false;
		data->eating_repeat_time = 0;
	}
	if (error == ERROR)
		return (ERROR);
	data->forks_mutex = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	for (int i = 0; i < data->num_of_philos; i++)////////////////////////////////////
		pthread_mutex_init(&data->forks_mutex[i], NULL);
	pthread_mutex_init(&data->main_mutex, NULL);
	pthread_mutex_init(&data->printing_mutex, NULL);
	data->simulation_starting_time = get_curr_time_in_ms();
	return (SUCCESS);
}

void	initialize_philosophers_vars(t_philosophers **philosophers, t_data *data)
{
	int		i;

	i = 0;
	*philosophers = malloc(sizeof(t_philosophers) * data->num_of_philos);
	while (i < data->num_of_philos)
	{
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].time_to_die_in_ms = 0;
		pthread_mutex_init(&(*philosophers)[i].death_mutex, NULL);
		i++;
	}
}

void	destroy_mutexes(t_data	*data, t_philosophers *philosopher)
{
	int		i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&philosopher[i].death_mutex);
		pthread_mutex_unlock(&data->forks_mutex[i]);
		pthread_mutex_destroy(&data->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->main_mutex);
	pthread_mutex_destroy(&data->printing_mutex);
}

void	free_allocated_data(t_philosophers **philosophers)
{
	free(*philosophers);
	*philosophers = NULL;
}

void	create_thread_per_philosopher(t_data *data)
{
	int		i;
	pthread_t thread_id;
	t_philosophers	*philosophers;

	i = 0;
	pthread_mutex_lock(&data->main_mutex);
	initialize_philosophers_vars(&philosophers, data);
	while (i < data->num_of_philos)
	{
		pthread_create(&thread_id, NULL, simulation, (void *)&philosophers[i]);
		pthread_detach(thread_id);
		usleep(100);
		i++;
	}
	pthread_mutex_lock(&data->main_mutex);
	destroy_mutexes(data, philosophers);
	free_allocated_data(&philosophers);
}

int main(int argc, char **argv)
{
	int					return_code;

    if (argc == MAX_ARGS_NUM || argc == MAX_ARGS_NUM + OPTIONAL_ARG)
    {
		return_code = initialize_data(&data, argv + 1);
		if (return_code == ERROR)
		{
			printf("Error\n");
			return (0);
		}
		create_thread_per_philosopher(&data);
    }
	else
		printf("Error\n");
    return (0);
}
