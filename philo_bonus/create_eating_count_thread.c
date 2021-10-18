/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_eating_count_thread.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:27:25 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/18 18:59:39 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	*eating_count_thread(void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	// while (true)
	// {
	// 	if (data->num_of_philos_completed_eating == data->num_of_philos)
	// 		break ;
	// 	usleep(ONE_MS_IN_US);
	// }
	int		i;

	i = 0;
	while (i++ < data->num_of_philos)
		sem_wait(data->eating_time_sem);
	sem_wait(data->eating_time_sem);
	printf(">>>%d<<<\n", 42);
	sem_post(data->main_sem);
	return (NULL);
}

void	create_eating_count_thread(t_data *data)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, eating_count_thread, (void *)data);
	pthread_detach(thread_id);
}
