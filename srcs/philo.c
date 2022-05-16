/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:38:43 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/16 16:09:53 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	controller(t_args *args)
{
	uint64_t	time;
	uint64_t	i;

	i = 0;
	while (1)
	{
		i++;
		if (i == args->nb_ph)
			i = 0;
		time = args->philos[i].last_meal + args->time_to_die;
		if (!args->philos[i].is_eating && get_time_now() > time)
		{
			time = get_time_now() - args->start_time;
			printf("%llu %llu died\n", get_time_now() - args->start_time, i + 1);
			exit(0);
		}
		time_sleep_checker(&args->philos[i], 30);
	}
}

void	*philosopher(void *philo_arg)
{
	t_philo		*philo;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		pick_shopstick(philo);
		eating_time(philo);
		leave_shopstick(philo);
		thinking_time(philo);
	}
}

int	main(int ac, char **av)
{
	pthread_t	*th;
	t_args		args;
	uint64_t			i;

	check_av(ac, av);
	args.nb_ph = ft_atoi(av[1]);
	if (args.nb_ph > 1000)
		return(printf("Big amount of philos, Malloc issue.\n"));
	args.start_time = get_time_now();
	init_philos(ac, av, &args);
	th = malloc(sizeof(pthread_t) * args.nb_ph);
	if (!th)
		return (-1);
	i = -1;
	while (++i < args.nb_ph)
	{
		if (pthread_create(&th[i], NULL, &philosopher, &args.philos[i]))
			exit(printf("Issue in thread creation\n"));
		my_sleep(100);
	}
	controller(&args);
	i = -1;
	while (++i < args.nb_ph)
		pthread_join(th[i], NULL);
	free_all(&args, th);
	return (0);
}
