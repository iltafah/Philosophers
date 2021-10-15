/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:30:07 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/15 21:03:36 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	pick_up_forks(int philo_id)
{
			// printf("%d\n", data.num_of_philos);
	if (philo_id % 2 == 1)
	{
		pthread_mutex_lock(&data.forks_mutex[philo_id % data.num_of_philos]);
		print_status(philo_id, taken_fork);	
		pthread_mutex_lock(&data.forks_mutex[philo_id - 1]);
		print_status(philo_id, taken_fork);
	}
	else if (philo_id % 2 == 0)
	{
		pthread_mutex_lock(&data.forks_mutex[philo_id - 1]);
		print_status(philo_id, taken_fork);
		pthread_mutex_lock(&data.forks_mutex[philo_id % data.num_of_philos]);
		print_status(philo_id, taken_fork);
	}
}

void	drop_forks(int philo_id)
{
	pthread_mutex_unlock(&data.forks_mutex[philo_id - 1]);
	pthread_mutex_unlock(&data.forks_mutex[philo_id %  data.num_of_philos]);
}

void	eat_spaghetti(t_philosophers *philo)
{
	int		remaining_time;

	remaining_time = data.time_to_die - data.time_to_eat;
	pthread_mutex_lock(&philo->death_mutex);
	print_status(philo->id, eating);
	usleep(data.time_to_eat * one_ms_in_us);
	drop_forks(philo->id);
	philo->time_to_die_in_ms = get_curr_time_in_ms() + remaining_time;
	pthread_mutex_unlock(&philo->death_mutex);
}

void	sleeping_time(int philo_id)
{
	print_status(philo_id, sleeping);
	usleep(data.time_to_sleep * one_ms_in_us);
}

void	*simulation(void *given_philo)
{
	int				repated_times;
	pthread_t		death_thread_id;
	t_philosophers	*curr_philo;	

	repated_times = 0;
	curr_philo = (t_philosophers *)given_philo;
	pthread_create(&death_thread_id, NULL, death_thread, (void*)curr_philo);
	pthread_detach(death_thread_id);
	while (true)
	{
		if (data.repeating_option == true &&
			++repated_times > data.eating_repeat_time)
			break ;
		pick_up_forks(curr_philo->id);
		eat_spaghetti(curr_philo);
		sleeping_time(curr_philo->id);
		print_status(curr_philo->id, thinking);
	}
	pthread_mutex_unlock(&data.main_mutex);
	return (NULL);
}
