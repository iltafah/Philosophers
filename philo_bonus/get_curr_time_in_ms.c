/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curr_time_in_ms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:26:34 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/17 14:38:22 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

long int	get_curr_time_in_ms(void)
{
	struct timeval	time_struct;
	long int		unix_time_in_us;
	long int		curr_time_in_ms;

	gettimeofday(&time_struct, NULL);
	unix_time_in_us = (time_struct.tv_sec * ONE_S_IN_US) + time_struct.tv_usec;
	curr_time_in_ms = unix_time_in_us * ONE_US_IN_MS;
	return (curr_time_in_ms);
}
