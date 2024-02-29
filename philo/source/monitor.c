/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 05:07:50 by lboudjel          #+#    #+#             */
/*   Updated: 2024/02/29 22:18:43 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	monitoring(t_philo *philo)
{
	while (1)
	{
		if (philo->args->must_eat != -1 && everyone_ate(philo))
			return (1);
		if (check_death(philo))
			return (1);
	}
}

int	everyone_ate(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nbr_philo)
	{
		pthread_mutex_lock(&philo->args->every_ate);
		if (philo->args->everyone_ate == philo->args->nbr_philo)
		{
			pthread_mutex_unlock(&philo->args->every_ate);
			return (1);
		}
		pthread_mutex_unlock(&philo->args->every_ate);
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].meal_eaten);
		if (philo[0].args->time_to_die <= (get_time() - philo[i].last_meal))
		{
			pthread_mutex_lock(&philo->args->death_mutex);
			philo->args->died = 1;
			pthread_mutex_unlock(&philo->args->death_mutex);
			pthread_mutex_lock(&philo[0].args->print);
			printf("%lld %i %s\n", get_time() - philo[0].whattimeisit,
				philo[i].philo_id, "died");
			pthread_mutex_unlock(&philo[0].args->print);
			return (pthread_mutex_unlock(&philo[i].meal_eaten), 1);
		}
		pthread_mutex_unlock(&philo[i].meal_eaten);
		i++;
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->args->death_mutex);
	is_dead = philo->args->died;
	pthread_mutex_unlock(&philo->args->death_mutex);
	return (is_dead);
}

void	unlock_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}
