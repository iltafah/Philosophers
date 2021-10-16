/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:30:43 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/16 19:02:58 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	*death_thread(void *given_philo)
{
	t_data			*data;
	t_philosophers	*curr_philo;

	data = get_data_struct(get, NULL);
	curr_philo = (t_philosophers *)given_philo;
	curr_philo->time_to_die_in_ms = get_curr_time_in_ms() + data->time_to_die;
	while (true)
	{
		pthread_mutex_lock(&curr_philo->death_mutex);
		if (get_curr_time_in_ms() > curr_philo->time_to_die_in_ms)
			break ;
		pthread_mutex_unlock(&curr_philo->death_mutex);
		usleep(500);
	}
	print_status(curr_philo->id, death, data);
	pthread_mutex_unlock(&data->main_mutex);
	return (NULL);
}
