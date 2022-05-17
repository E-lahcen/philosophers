/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:49:04 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/17 19:42:35 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_philos(int ac, char **av, t_args *args)
{
	uint64_t	i;

	args->philos = (t_philo *)malloc(sizeof(t_philo) * args->nb_ph);
	args->shopsticks = malloc(sizeof(pthread_mutex_t) * args->nb_ph);
	if (!args->philos || !args->shopsticks)
		return (0);
	i = -1;
	while (++i < args->nb_ph)
	{
		args->philos[i].id = i;
		args->philos[i].shopstick_r = (i + 1) % args->nb_ph;
		args->philos[i].shopstick_l = i;
		args->philos[i].args = args;
		args->philos[i].is_eating = 0;
		args->philos[i].last_meal = get_time_now();
		if (ac == 6)
			args->philos[i].must_eat = ft_atoi(av[5]);
		else
			args->philos[i].must_eat = -1;
		pthread_mutex_init(&args->philos[i].lock_controller, NULL);
	}
	init_args(av, args);
	return (1);
}

void	init_args(char **av, t_args *args)
{
	uint64_t	i;

	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->ph_must_eat = 0;
	i = -1;
	while (++i < args->nb_ph)
		pthread_mutex_init(&args->shopsticks[i], NULL);
	pthread_mutex_init(&args->print_lock, NULL);
}

uint64_t	get_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	time_sleep_checker(t_philo *philo, int loop)
{
	uint64_t	time;
	int			a;

	a = -1;
	while (++a < loop)
	{
		if (!philo->is_eating && get_time_now() > philo->last_meal \
		+ philo->args->time_to_die)
		{
			time = get_time_now() - philo->args->start_time;
			printf("%llu %d died\n", time, philo->id + 1);
			return (0);
		}
		usleep(10);
	}
	return (1);
}

void	my_sleep(uint64_t pause)
{
	uint64_t	time;

	time = get_time_now();
	while (get_time_now() < time + pause)
		usleep(50);
}
