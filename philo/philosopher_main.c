/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:01 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/15 21:03:30 by iltafah          ###   ########.fr       */
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
		// printf("%d\n",data.num_of_philos);
		create_thread_per_philosopher(&data);
    }
	else
		printf("Error\n");
    return (0);
}
