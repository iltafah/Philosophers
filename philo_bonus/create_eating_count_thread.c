/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_eating_count_thread.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:27:25 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/20 14:49:10 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	wait_for_processes_to_exit(t_data *data)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i < data->num_of_philos)
	{
		waitpid(data->processes_ids[i], &exit_status, 0);
		i++;
	}
}

void	*eating_count_thread(void *data_ptr)
{
	t_data	*data;
	int		curr_eating_time;

	data = (t_data *)data_ptr;
	curr_eating_time = 0;
	while (true)
	{
		sem_wait(data->eating_time_sem);
		curr_eating_time++;
		if (curr_eating_time == data->num_of_philos)
			break ;
	}
	wait_for_processes_to_exit(data);
	sem_post(data->main_lock_sem);
	return (NULL);
}

void	create_eating_count_thread(t_data *data)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, eating_count_thread, (void *)data);
	pthread_detach(thread_id);
}
