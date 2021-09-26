/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:18:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/22 17:32:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	init_mutexes(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->philo_amount)
	{
		if (pthread_mutex_init(&args->fork_mutex[i], NULL) != 0)
			error(MUTEX_FAIL, NULL);
		i++;
	}
	if (pthread_mutex_init(&args->write_mutex, NULL) != 0)
		error(MUTEX_FAIL, NULL);
}

t_args	set_args(char **av)
{
	unsigned int	i;
	t_args			args;

	i = 0;
	args.philo_amount = (unsigned int)ft_atoi(av[1]);
	args.time_to_die = (unsigned long long)ft_atoi(av[2]);
	args.time_to_eat = (unsigned long long)ft_atoi(av[3]);
	args.time_to_sleep = (unsigned long long)ft_atoi(av[4]);
	args.times_philosopher_eat = (unsigned int)ft_atoi(av[5]);
	args.fork_mutex = malloc(sizeof(pthread_mutex_t) * args.philo_amount);
	init_mutexes(&args);
	return (args);
}

void	create_threads(t_args args, t_philo *philos)
{
	int				i;
	int				err;

	i = 0;
	err = 0;
	while ((unsigned int)i < args.philo_amount)
	{
		err = pthread_create(&philos[i].routine_id, NULL, philo_routine, &philos[i]);
		if (err != 0)
			error(THREAD_FAIL, philos);
		pthread_detach(philos[i].routine_id);
		i++;
	}
	i = 0;
	while ((unsigned int)i < args.philo_amount)
	{
		err = pthread_create(&philos[i].checker_id, NULL, death_checker, &philos[i]);
		if (err != 0)
			error(THREAD_FAIL, philos);
		pthread_detach(philos[i].checker_id);
		i++;
	}
}
