/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:27:58 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/19 14:44:21 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	print_status(int philo_id, t_status_msg msg_id, t_data *data)
{
	long int		curr_time_in_ms;
	long int		simulation_curr_time_ms;
	static char		colors[5][8] = {WHT, GRN, CYN, YEL, RED};
	static char		messages[5][20] =
	{
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"is died"
	};

	sem_wait(data->printing_sem);
	curr_time_in_ms = get_curr_time_in_ms();
	simulation_curr_time_ms = curr_time_in_ms - data->simulation_starting_time;
	printf("%s%ld\t%d", WHT, simulation_curr_time_ms, philo_id);
	printf("\t%s%s%s\n", colors[msg_id], messages[msg_id], RST);
	if (msg_id == death)
		return ;
	sem_post(data->printing_sem);
}
