/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread_per_philosopher.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:32:06 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/15 21:03:25 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

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

void	initialize_philos_vars(t_philosophers **philosophers, t_data *data)
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

void	create_thread_per_philosopher(t_data *data)
{
	int				i;
	pthread_t		thread_id;
	t_philosophers	*philosophers;
	i = 0;
	pthread_mutex_lock(&data->main_mutex);
	initialize_philos_vars(&philosophers, data);
	while (i < data->num_of_philos)
	{
		// printf("%d\n",data->num_of_philos);
		pthread_create(&thread_id, NULL, simulation, (void *)&philosophers[i]);
		pthread_detach(thread_id);
		i++;
	}
	pthread_mutex_lock(&data->main_mutex);
	destroy_mutexes(data, philosophers);
	free_allocated_data(&philosophers);
}
