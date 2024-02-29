/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:10:26 by lboudjel          #+#    #+#             */
/*   Updated: 2024/02/29 22:18:43 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	tempo(long int time_in_ms, t_philo *philo)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
	{
		if ((philo->args->nbr_philo != 1) && is_dead(philo))
			return ;
		usleep(100);
	}
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print_msg(t_philo *philo, char *str)
{
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->args->print);
	printf("%lld %i %s\n", get_time() - philo->whattimeisit, philo->philo_id,
		str);
	pthread_mutex_unlock(&philo->args->print);
	return (0);
}

void	one_philo(t_philo *philo)
{
	pthread_create(&philo[0].thread, NULL, routine_one_philo, &philo[0]);
	pthread_join(philo[0].thread, NULL);
}

int	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_msg(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(&philo->right_fork);
		if (print_msg(philo, "has taken a fork"))
			return (pthread_mutex_unlock(&philo->right_fork),
				pthread_mutex_unlock(philo->left_fork), 1);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		if (print_msg(philo, "has taken a fork"))
			return (pthread_mutex_unlock(&philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
		if (print_msg(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(&philo->right_fork), 1);
	}
	return (0);
}
