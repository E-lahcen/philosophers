/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:38:43 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/17 19:41:36 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	controller(t_args *args)
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
			pthread_mutex_lock(&args->print_lock);
			printf("%llu %llu died\n", get_time_now() - args->start_time, i + 1);
			return (0 * free_all(args, args->th));
		}
		if (args->ph_must_eat == args->nb_ph)
		{
			pthread_mutex_lock(&args->print_lock);
			return (0 * free_all(args, args->th));
		}
		my_sleep(50);
	}
	return (1);
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
	return (0);
}

int	main(int ac, char **av)
{
	t_args		args;
	uint64_t	i;

	if (!check_ac(ac, av, &args) || !check_av(ac, av) || \
!init_philos(ac, av, &args))
		return (-1);
	args.th = malloc(sizeof(pthread_t) * args.nb_ph);
	if (!args.th)
		return (-1);
	i = -1;
	while (++i < args.nb_ph)
	{
		if (pthread_create(&args.th[i], NULL, &philosopher, &args.philos[i]))
			return (printf("Issue in thread creation\n"));
		my_sleep(10);
	}
	i = -1;
	if (!controller(&args))
		return (-1);
	while (++i < args.nb_ph)
		pthread_join(args.th[i], NULL);
	free_all(&args, args.th);
	return (0);
}
