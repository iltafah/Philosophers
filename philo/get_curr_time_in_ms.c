/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curr_time_in_ms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:26:34 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/15 20:27:12 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

long int	get_curr_time_in_ms(void)
{
	struct timeval	time_struct;
	long int		unix_time_in_us;
	long int		curr_time_in_ms;

	gettimeofday(&time_struct, NULL);
	unix_time_in_us = (time_struct.tv_sec * one_s_in_us) + time_struct.tv_usec;
	curr_time_in_ms = unix_time_in_us * one_us_in_ms;
	return (curr_time_in_ms);
}
