/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:49:04 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/21 17:08:39 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	init_philos(int ac, char **av, t_args *args)
{
	uint64_t	i;

	args->nb_ph = ft_atoi(av[1]);
	if (args->nb_ph > 200)
		exit(printf("Lot of philosophers ASSAT.\n"));
	args->philos = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!args->philos)
		exit(0);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		args->philos[i].id = i;
		args->philos[i].args = args;
		args->philos[i].is_eating = 0;
		if (ac == 6)
			args->philos[i].must_eat = ft_atoi(av[5]);
		else
			args->philos[i].must_eat = -1;
		args->philos[i].last_meal = get_time_now();
	}
	init_args(ac, av, args);
}

void	init_args(int ac, char **av, t_args *args)
{
	if (ac == 6)
		args->ph_must_eat = 0;
	else
		args->ph_must_eat = -1;
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->dead = 0;
	sem_unlink("/Semaphore_shopstick");
	args->shopsticks = sem_open("/Semaphore_shopstick", \
O_CREAT, S_IRWXU, args->nb_ph);
	sem_unlink("Semaphore_print_message");
	args->lock_print = sem_open("Semaphore_print_message", O_CREAT, S_IRWXU, 1);
}

uint64_t	get_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_check(t_philo *philo)
{
	if (!philo->is_eating && \
get_time_now() > philo->last_meal + philo->args->time_to_die)
	{
		sem_wait(philo->args->lock_print);
		printf("%llu %d died\n", get_time_now() - \
philo->args->start_time, philo->id + 1);
		kill_all(philo->args);
		exit (0);
	}
}
