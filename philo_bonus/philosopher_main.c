/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:01 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/20 15:21:21 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

int	convert_arg_to_int(char *argv, int *error)
{
	int			i;
	long int	num;

	i = 0;
	num = 0;
	if (argv[0] == '\0')
		*error = ERROR;
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

void	initialize_semaphores(t_data *data)
{
	sem_unlink("forks");
	data->forks_sem = sem_open("forks", O_CREAT, 0777, data->num_of_philos);
	sem_unlink("print");
	data->printing_sem = sem_open("print", O_CREAT, 0777, 1);
	sem_unlink("main");
	data->main_lock_sem = sem_open("main", O_CREAT, 0777, 0);
	sem_unlink("eating");
	data->eating_time_sem = sem_open("eating", O_CREAT, 0777, 0);
}

int	initialize_data_struct(t_data *data, char **argv)
{
	int				error;

	error = NONE;
	data->eating_repeat_time = 0;
	data->num_of_philos = convert_arg_to_int(argv[0], &error);
	data->time_to_die = convert_arg_to_int(argv[1], &error);
	data->time_to_eat = convert_arg_to_int(argv[2], &error);
	data->time_to_sleep = convert_arg_to_int(argv[3], &error);
	if (argv[4] != NULL)
		data->eating_repeat_time = convert_arg_to_int(argv[4], &error);
	if (error == ERROR || data->num_of_philos == 0)
		return (ERROR);
	initialize_semaphores(data);
	data->processes_ids = malloc(sizeof(pid_t) * data->num_of_philos);
	data->simulation_starting_time = get_curr_time_in_ms();
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		return_code;

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
		create_process_per_philosopher(&data);
	}
	else
		printf("Error\n");
	return (0);
}
