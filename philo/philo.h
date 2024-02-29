/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:52:31 by lboudjel          #+#    #+#             */
/*   Updated: 2024/02/29 22:11:21 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct args
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				died;
	int				everyone_ate;
	int				finish_eating;
	pthread_mutex_t	finito_eating;
	int				flag;
	pthread_mutex_t	every_ate;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print;
}					t_args;

typedef struct philo
{
	int				philo_id;
	long long		last_meal;
	long long		whattimeisit;
	int				meal;
	pthread_mutex_t	meal_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		thread;
	t_args			*args;
}					t_philo;

// parsing.c
int					ft_atoi(char *str);
int					is_num(char **argv);
int					init_struct(t_args *args, int argc, char **argv);

// main.c
int					init_mutex(t_args *args, t_philo *philo);
int					philo_init(t_args *args, t_philo *philo);
void				*a_table(t_philo *philo, t_args *args);
void				debarasser(t_philo *philo, t_args *args);

// utils.c
void				tempo(long int time_in_ms, t_philo *philo);
long int			get_time(void);
int					print_msg(t_philo *philo, char *str);
void				one_philo(t_philo *philo);
int					take_forks(t_philo *philo);

// routine.c
void				*routine(void *structure);
int					miam(t_philo *philo);
int					rompich(t_philo *philo);
int					thinking(t_philo *philo);
void				*routine_one_philo(void *structure);

// monitor.c
int					monitoring(t_philo *philo);
int					everyone_ate(t_philo *philo);
int					check_death(t_philo *philo);
int					is_dead(t_philo *philo);
void				unlock_fork(t_philo *philo);

#endif

/*
IF NBPHILO EST PAIR

	ILS VIVENT
		timetodie >= timetoeat + timetosleep
		410			200			200
		510			300			200

IF NBPHILO EST IMPAIR

	ILS VIVENT
		timetodie >= (timtoeat + timetosleep) * 1.5
		610			200			200
*/