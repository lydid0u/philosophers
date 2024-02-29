/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:45:00 by lboudjel          #+#    #+#             */
/*   Updated: 2024/02/29 22:21:23 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *structure)
{
	t_philo	*phil;

	phil = (t_philo *)structure;
	if (phil->philo_id % 2 == 1)
		tempo(phil->args->time_to_eat, phil);
	while (1)
	{
		if (miam(phil))
			break ;
		if (rompich(phil))
			break ;
		if (thinking(phil))
			break ;
		if (phil->args->nbr_philo % 2 == 1)
			tempo(50, phil);
	}
	return (NULL);
}

int	miam(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (print_msg(philo, "is eating"))
	{
		unlock_fork(philo);
		return (1);
	}
	tempo(philo->args->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_eaten);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_eaten);
	unlock_fork(philo);
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->meal_eaten);
	philo->meal++;
	if (philo->meal == philo->args->must_eat)
	{
		pthread_mutex_lock(&philo->args->every_ate);
		philo->args->everyone_ate++;
		pthread_mutex_unlock(&philo->args->every_ate);
		return (pthread_mutex_unlock(&philo->meal_eaten), 1);
	}
	pthread_mutex_unlock(&philo->meal_eaten);
	return (0);
}

int	rompich(t_philo *philo)
{
	if (print_msg(philo, "is sleeping"))
		return (1);
	tempo(philo->args->time_to_sleep, philo);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (print_msg(philo, "is thinking"))
		return (1);
	if (philo->args->time_to_sleep < philo->args->time_to_eat)
		tempo(philo->args->time_to_eat - philo->args->time_to_sleep, philo);
	return (0);
}

void	*routine_one_philo(void *structure)
{
	t_philo	*phil;

	phil = (t_philo *)structure;
	pthread_mutex_lock(&phil->right_fork);
	pthread_mutex_lock(&phil->args->print);
	printf("%lld %i has taken a fork\n", get_time() - phil->whattimeisit,
		phil->philo_id);
	pthread_mutex_unlock(&phil->args->print);
	tempo(phil->args->time_to_die, phil);
	pthread_mutex_unlock(&phil->right_fork);
	if (is_dead(phil))
	{
		pthread_mutex_lock(&phil[0].args->print);
		printf("%lld %i %s\n", get_time() - phil[0].whattimeisit,
			phil[0].philo_id, "died");
		pthread_mutex_unlock(&phil[0].args->print);
		return (NULL);
	}
	return (NULL);
}
