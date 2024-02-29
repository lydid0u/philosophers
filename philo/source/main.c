/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:54:38 by lboudjel          #+#    #+#             */
/*   Updated: 2024/02/29 22:18:43 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_mutex(t_args *args, t_philo *philo)
{
	(void)philo;
	if (pthread_mutex_init(&args->print, NULL) != 0)
		return (printf("Init mutex : print mutex has fail\n"), 0);
	if (pthread_mutex_init(&args->death_mutex, NULL) != 0)
		return (printf("Init mutex : death mutex has fail\n"), 0);
	if (pthread_mutex_init(&args->finito_eating, NULL) != 0)
		return (printf("Init mutex : finish eating mutex has fail\n"), 0);
	if (pthread_mutex_init(&args->every_ate, NULL) != 0)
		return (printf("Init mutex : everyone ate mutex has fail\n"), 0);
	return (1);
}

int	philo_init(t_args *args, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		if (pthread_mutex_init(&philo[i].right_fork, NULL) != 0)
			return (printf("Init mutex : right fork mutex has fail\n"), 0);
		if (pthread_mutex_init(&philo[i].meal_eaten, NULL) != 0)
			return (printf("Init mutex : meal eaten mutex has fail\n"), 0);
		philo[i].philo_id = i + 1;
		philo[i].args = args;
		philo[i].whattimeisit = get_time();
		philo[i].last_meal = get_time();
		if (i != 0)
			philo[i].left_fork = &philo[i - 1].right_fork;
		else
			philo[i].left_fork = &philo[args->nbr_philo - 1].right_fork;
		i++;
	}
	if (!init_mutex(args, philo))
		return (0);
	return (1);
}

void	*a_table(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	monitoring(philo);
	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (NULL);
}

void	debarasser(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_mutex_destroy(&philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(&args->death_mutex);
	pthread_mutex_destroy(&args->every_ate);
	pthread_mutex_destroy(&args->print);
	pthread_mutex_destroy(&philo->meal_eaten);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	static t_args	args;

	if (argc != 5 && argc != 6)
		return (printf("Too many or not enough arguments\n"), 1);
	if (is_num(argv))
		return (1);
	if (init_struct(&args, argc, argv))
		return (1);
	philo = malloc(sizeof(t_philo) * args.nbr_philo);
	if (!philo)
		return (1);
	philo_init(&args, philo);
	if (args.nbr_philo == 1)
	{
		one_philo(philo);
		return (1);
	}
	a_table(philo, &args);
	debarasser(philo, &args);
}
