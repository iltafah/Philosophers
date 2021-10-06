/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:31:01 by iltafah           #+#    #+#             */
/*   Updated: 2021/10/06 17:14:58 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	simulation()
{
	
}

int	convert_arg_to_int(char *argv, int *error)
{
	int			i;
	long int	num;
	
	i = 0;
	num = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
		{
			*error = ERROR;
			return (ERROR);
		}
		num = (num * 10) + (argv[i] - '0');
		i++;
	}
	if (num > MAX_INT)
	{
		*error = ERROR;
		return (ERROR);
	}
	return (num);
}

int	initialize_philo_vars(t_philo_vars *philo_vars, char **argv)
{
	int		error;

	error = NONE;
	philo_vars->num_of_philos = convert_arg_to_int(argv[0], &error);
	philo_vars->time_to_die = convert_arg_to_int(argv[1], &error);
	philo_vars->time_to_eat = convert_arg_to_int(argv[2], &error);
	philo_vars->time_to_sleep = convert_arg_to_int(argv[3], &error);
	if (argv[4] != NULL)
		philo_vars->eating_repeat_time = convert_arg_to_int(argv[4], &error);
	else
		philo_vars->eating_repeat_time = 0;
	if (error == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_philo_vars	philo_vars;
	int				return_code;

    if (argc == MAX_ARGS_NUM || argc == MAX_ARGS_NUM + OPTIONAL_ARG)
    {
		return_code = initialize_philo_vars(&philo_vars, argv + 1);
		if (return_code == ERROR)
		{
			printf("Error\n");
			return (0);
		}
    }
	else
		printf("Error\n");
    return (0);
}
