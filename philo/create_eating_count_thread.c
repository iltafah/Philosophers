/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_eating_count_thread.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:27:25 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/20 12:53:41 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	*eating_count_thread(void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	while (true)
	{
		if (data->num_of_philos_completed_eating == data->num_of_philos)
			break ;
		usleep(ONE_MS_IN_US);
	}
	pthread_mutex_unlock(&data->main_mutex);
	return (NULL);
}

void	create_eating_count_thread(t_data *data)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, eating_count_thread, (void *)data);
	pthread_detach(thread_id);
}
