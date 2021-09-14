/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:00:03 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/14 23:50:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

# define ARGS_FAIL 1
# define THREAD_FAIL 2
# define MUTEX_FAIL 3

# define PHILO_FORK 30
# define PHILO_EAT 31
# define PHILO_DEATH 32
# define PHILO_SLEEP 33
# define PHILO_THINK 34

typedef unsigned long long	t_millisecond;

typedef struct s_args
{
	int				*forks;
	unsigned int	philo_amount;
	unsigned int	times_philosopher_eat;
	t_millisecond	origin_time;
	t_millisecond	time_to_die;
	t_millisecond	time_to_eat;
	t_millisecond	time_to_sleep;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*fork_mutex;	
}				t_args;

typedef struct s_philo
{
	int				*forks[2];
	unsigned int	num;
	unsigned int	meals;
	bool			is_dead;
	t_millisecond	last_eat;
	t_args			*args;
	pthread_t		id;
}				t_philo;

void			create_threads(t_args args, t_philo *philos);

t_philo			set_philo(int i);
t_philo			*create_philos(t_args *args);
t_args			set_args(char **av);

void			*philo_routine(void *philo);

void			philo_write(t_philo *philo, int status);
void			philo_sleep(t_philo *philo);
void			philo_eat(t_philo *philo);
int				philo_death(t_millisecond timestamp, t_philo *philo);

t_millisecond	to_mili(struct timeval tv);
t_millisecond	get_time(t_philo *philo);
int				ft_atoi(const char *nptr);
void			error(int code, t_philo *philos);

#endif