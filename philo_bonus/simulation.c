/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:30:07 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/18 21:54:56 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	pick_up_forks(int philo_id, t_data *data)
{
	sem_wait(data->forks_semaphore);
	print_status(philo_id, taken_fork, data);
	sem_wait(data->forks_semaphore);
	print_status(philo_id, taken_fork, data);
}

void	drop_forks(t_data *data)
{
	sem_post(data->forks_semaphore);
	sem_post(data->forks_semaphore);
}

void	eat_spaghetti(t_philosophers *philo, t_data *data)
{
	int		remaining_time;

	remaining_time = data->time_to_die - data->time_to_eat;
	sem_wait(philo->death_sem);
	print_status(philo->id, eating, data);
	usleep(data->time_to_eat * ONE_MS_IN_US);
	drop_forks(data);
	data->philos_eating_time++;
	philo->time_to_die_in_ms = get_curr_time_in_ms() + remaining_time;

	sem_post(data->eating_time_sem);

	sem_post(philo->death_sem);
}

void	sleeping_time(int philo_id, t_data *data)
{
	print_status(philo_id, sleeping, data);
	usleep(data->time_to_sleep * ONE_MS_IN_US);
}

void	*simulation(void *given_philo)
{
	t_data			*data;
	t_philosophers	*curr_philo;
	pthread_t		death_thread_id;
	int				eating_time;

	eating_time = 0;
	data = get_data_struct(get, NULL);
	curr_philo = (t_philosophers *)given_philo;
	pthread_create(&death_thread_id, NULL, death_thread, (void *)curr_philo);
	pthread_detach(death_thread_id);
	while (true)
	{
		pick_up_forks(curr_philo->id, data);
		eat_spaghetti(curr_philo, data);
		// eating_time++;
		// if (data->repeating_option == true
		// 	&& eating_time == data->eating_repeat_time)
		// {
		// 	sem_post(data->eating_time_sem);
		// 	break ;
		// }
		sleeping_time(curr_philo->id, data);
		print_status(curr_philo->id, thinking, data);
	}
	return (NULL);
}
