/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:20:19 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/16 10:20:35 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

t_data	*get_data_struct(t_option option, t_data *data_to_set_addr)
{
	static t_data	*static_data_ptr = NULL;

	if (option == get)
		return (static_data_ptr);
	else if (option == set)
		static_data_ptr = data_to_set_addr;
	return (NULL);
}
