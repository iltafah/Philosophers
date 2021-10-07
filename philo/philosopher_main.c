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

void	*simulation(void *given_philo)
{
	struct timeval	time_struct;
	int				repated_times;
	t_philosophers	curr_philo;
	
	repated_times = 0;
	curr_philo = *(t_philosophers *)given_philo;
	while (repated_times < philo_vars.eating_repeat_time)
	{
		gettimeofday(&time_struct, NULL);
		if (curr_philo.is_fork_available == available)
		{
			pthread_mutex_lock(&philo_vars.forks_mutex[curr_philo.id - 1]);
			printf("%ld %d has taken a fork\n", ((time_struct.tv_sec + (time_struct.tv_usec / 1000000))/1000 - philo_vars.simulation_starting_time), curr_philo.id);
			curr_philo.is_fork_available = not_available;
			pthread_mutex_lock(&philo_vars.forks_mutex[curr_philo.id %  philo_vars.num_of_philos]);
			*(curr_philo.next_fork_ptr) = not_available;
			printf("%ld %d has taken a fork\n", ((time_struct.tv_sec + (time_struct.tv_usec / 1000000))/1000 - philo_vars.simulation_starting_time), curr_philo.id);
		}
		printf("%ld %d is eating\n", ((time_struct.tv_sec + (time_struct.tv_usec / 1000000))/1000 - philo_vars.simulation_starting_time), curr_philo.id);
		usleep(philo_vars.time_to_eat * 1000);

		pthread_mutex_unlock(&philo_vars.forks_mutex[curr_philo.id - 1]);
		pthread_mutex_unlock(&philo_vars.forks_mutex[curr_philo.id %  philo_vars.num_of_philos]);
		gettimeofday(&time_struct, NULL);
		printf("%ld %d is sleeping\n", ((time_struct.tv_sec + (time_struct.tv_usec / 1000000))/1000 - philo_vars.simulation_starting_time), curr_philo.id);
		repated_times++;
	}
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

int	initialize_philo_vars(t_philo_vars *philo_vars, char **argv)
{
	int				error;
	struct timeval	time_struct;

	error = NONE;
	philo_vars->num_of_philos = convert_arg_to_int(argv[0], &error);
	philo_vars->time_to_die = convert_arg_to_int(argv[1], &error);
	philo_vars->time_to_eat = convert_arg_to_int(argv[2], &error);
	philo_vars->time_to_sleep = convert_arg_to_int(argv[3], &error);
	if (argv[4] != NULL)
		philo_vars->eating_repeat_time = convert_arg_to_int(argv[4], &error);
	else
		philo_vars->eating_repeat_time = 0;
	if (error == ERROR)
		return (ERROR);
	// philo_vars->forks_availability = malloc(sizeof(t_is_available) * philo_vars->num_of_philos);
	philo_vars->forks_mutex = malloc(sizeof(pthread_mutex_t) * philo_vars->num_of_philos);
	for (int i = 0; i < philo_vars->num_of_philos; i++)
	{
		pthread_mutex_init(&philo_vars->forks_mutex[i], NULL);
		// philo_vars->forks_availability[i] = available;
	}
	gettimeofday(&time_struct, NULL);
	philo_vars->simulation_starting_time = (time_struct.tv_sec + (time_struct.tv_usec / 1000000)) / 1000;
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_philosophers	*philo_simulation;
	int					return_code;

    if (argc == MAX_ARGS_NUM || argc == MAX_ARGS_NUM + OPTIONAL_ARG)
    {
		return_code = initialize_philo_vars(&philo_vars, argv + 1);
		if (return_code == ERROR)
		{
			printf("Error\n");
			return (0);
		}
		//////////
		pthread_t *thread_id = malloc(sizeof(pthread_t) * 5);
		int			*philo_ids = malloc(sizeof(int) * 5);
		for (int id = 0; id < philo_vars.num_of_philos; id++)
			philo_ids[id] = id + 1;

		philo_simulation = malloc(sizeof(t_philosophers) * philo_vars.num_of_philos);

		int i = 0;
		while (i < philo_vars.num_of_philos)
		{
			philo_simulation[i].id = i + 1;
			philo_simulation[i].is_eating = false;
			philo_simulation[i].is_sleeping = false;
			philo_simulation[i].is_thinking = false;
			philo_simulation[i].is_fork_available = available;
			philo_simulation[i].next_fork_ptr = &philo_simulation[(i + 1) % philo_vars.num_of_philos].is_fork_available;
			i++;
		}
		
		
		i = 0;
		while (i < philo_vars.num_of_philos)
		{
			pthread_create(&thread_id[i], NULL, simulation, (void *)&philo_simulation[i]);
			pthread_detach(thread_id[i]);
			usleep(50);
			i++;
		}

while (1)
{
	
}

    }
	else
		printf("Error\n");
    return (0);
}
