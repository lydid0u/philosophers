/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:52:20 by lboudjel          #+#    #+#             */
/*   Updated: 2024/02/29 22:18:43 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int			i;
	long int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - 48;
		if (res > INT_MAX)
			return (printf("Int bigger than int max\n"), 0);
		i++;
	}
	return (res);
}

int	is_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Argument is not an int\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_struct(t_args *args, int argc, char **argv)
{
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	else
		args->must_eat = -1;
	if (args->nbr_philo > 1)
		args->died = 0;
	else
		args->died = 1;
	args->everyone_ate = 0;
	if (args->nbr_philo <= 0 || args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0 || args->must_eat == 0)
		return (1);
	return (0);
}
