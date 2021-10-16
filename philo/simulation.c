/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:30:07 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/16 20:21:13 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	pick_up_forks(int philo_id, t_data *data)
{
	if (philo_id % 2 == 1)
	{
		pthread_mutex_lock(&data->forks_mutex[philo_id % data->num_of_philos]);
		print_status(philo_id, taken_fork, data);	
		pthread_mutex_lock(&data->forks_mutex[philo_id - 1]);
		print_status(philo_id, taken_fork, data);
	}
	else if (philo_id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks_mutex[philo_id - 1]);
		print_status(philo_id, taken_fork, data);
		pthread_mutex_lock(&data->forks_mutex[philo_id % data->num_of_philos]);
		print_status(philo_id, taken_fork, data);
	}
}

void	drop_forks(int philo_id, t_data *data)
{
	pthread_mutex_unlock(&data->forks_mutex[philo_id - 1]);
	pthread_mutex_unlock(&data->forks_mutex[philo_id %  data->num_of_philos]);
}

void	eat_spaghetti(t_philosophers *philo, t_data *data)
{
	int		remaining_time;

	remaining_time = data->time_to_die - data->time_to_eat;
	pthread_mutex_lock(&philo->death_mutex);
	print_status(philo->id, eating, data);
	usleep(data->time_to_eat * one_ms_in_us);
	drop_forks(philo->id, data);
	philo->time_to_die_in_ms = get_curr_time_in_ms() + remaining_time;
	pthread_mutex_unlock(&philo->death_mutex);
}

void	sleeping_time(int philo_id, t_data *data)
{
	print_status(philo_id, sleeping, data);
	usleep(data->time_to_sleep * one_ms_in_us);
}

void	*simulation(void *given_philo)
{
	t_data			*data;
	t_philosophers	*curr_philo;
	int				eating_times;
	pthread_t		death_thread_id;

	eating_times = 0;
	data = get_data_struct(get, NULL);
	printf("sumilation = %p\n", &data->num_of_philos_completed_eating);
	curr_philo = (t_philosophers *)given_philo;
	pthread_create(&death_thread_id, NULL, death_thread, (void*)curr_philo);
	pthread_detach(death_thread_id);
	while (true)
	{
		pick_up_forks(curr_philo->id, data);
		eat_spaghetti(curr_philo, data);
		if (data->repeating_option == true &&
			++eating_times == data->eating_repeat_time)
		{
			data->num_of_philos_completed_eating++;
			pthread_mutex_lock(&curr_philo->death_mutex);
			break ;
		}
		sleeping_time(curr_philo->id, data);
		print_status(curr_philo->id, thinking, data);
	}
	// pthread_mutex_unlock(&data->main_mutex);
	return (NULL);
}
