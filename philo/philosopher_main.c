/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:01 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/16 20:22:35 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

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

int	initialize_data_struct(t_data *data, char **argv)
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
	data->num_of_philos_completed_eating = 0;
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

void	*eating_count_thread(void *data_ptr)
{
	t_data	*data;

	data = (t_data*)data_ptr;/////////////////////////////////////////////////////
	data = get_data_struct(get, NULL);
	while (true)
	{
		if (data->num_of_philos_completed_eating == data->num_of_philos)
			break ;
		usleep(one_ms_in_us);
	}
	pthread_mutex_unlock(&data->main_mutex);
	return (NULL);
}

void	create_eating_count_thread(t_data *data)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, eating_count_thread, (void *)&data);
	pthread_detach(thread_id);
}

int main(int argc, char **argv)
{
	int		return_code;
	t_data	data;

    if (argc == MAX_ARGS_NUM || argc == MAX_ARGS_NUM + OPTIONAL_ARG)
    {
		get_data_struct(set, &data);
		return_code = initialize_data_struct(&data, argv + 1);
		if (return_code == ERROR)
		{
			printf("Error\n");
			return (0);
		}
		create_eating_count_thread(&data);
		create_thread_per_philosopher(&data);
    }
	else
		printf("Error\n");
    return (0);
}
