/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:30:43 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/19 18:07:21 by iltafah          ###   ########.fr       */
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
		sem_wait(curr_philo->death_sem);
		if (get_curr_time_in_ms() > curr_philo->time_to_die_in_ms)
			break ;
		sem_post(curr_philo->death_sem);
		usleep(500);
	}
	print_status(curr_philo->id, death, data);
	sem_post(data->main_lock_sem);
	return (NULL);
}
