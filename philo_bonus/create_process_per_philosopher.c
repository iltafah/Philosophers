/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_per_philosopher.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:32:06 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/19 21:51:21 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	free_allocated_data(t_philosophers **philosophers, t_data *data)
{
	free(*philosophers);
	*philosophers = NULL;
	free(data->process_id);
	data->process_id = NULL;
}

void	clear_resources(t_philosophers **philosophers, t_data *data)
{
	free_allocated_data(philosophers, data);
	sem_close(data->main_lock_sem);
	sem_close(data->forks_sem);
	sem_close(data->printing_sem);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("main");
	sem_unlink("eating");
}

void	kill_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
		kill(data->process_id[i++], SIGKILL);
}

void	initialize_philos_vars(t_philosophers **philosophers, t_data *data)
{
	int		i;

	i = 0;
	*philosophers = malloc(sizeof(t_philosophers) * data->num_of_philos);
	while (i < data->num_of_philos)
	{
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].time_to_die_in_ms = 0;
		i++;
	}
}

void	create_process_per_philosopher(t_data *data)
{
	int				i;
	t_philosophers	*philosophers;

	i = 0;
	initialize_philos_vars(&philosophers, data);
	while (i < data->num_of_philos)
	{
		data->process_id[i] = fork();
		if (data->process_id[i] == 0)
		{
			sem_unlink("death");
			philosophers[i].death_sem = sem_open("death", O_CREAT, 0777, 1);
			simulation((void *)&philosophers[i]);
			exit(0);
		}
		else if (data->process_id[i] == -1)
		{
			printf("Error\n");
			exit(0);
		}
		i++;
	}
	sem_wait(data->main_lock_sem);
	kill_processes(data);
	clear_resources(&philosophers, data);
}
