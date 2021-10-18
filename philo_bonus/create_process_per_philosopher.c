/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_per_philosopher.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:32:06 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/18 17:43:31 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	free_allocated_data(t_philosophers **philosophers)
{
	free(*philosophers);
	*philosophers = NULL;
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
	pid_t			process_id;
	t_philosophers	*philosophers;

	i = 0;
	initialize_philos_vars(&philosophers, data);
	while (i < data->num_of_philos)
	{
		process_id = fork();
		if (process_id == 0)
		{
			sem_unlink("death");
			philosophers[i].death_sem = sem_open("death", O_CREAT, 0777, 1);
			simulation((void *)&philosophers[i]);
			exit(0);
		}
		i++;
	}
	sem_wait(data->main_sem);
}
