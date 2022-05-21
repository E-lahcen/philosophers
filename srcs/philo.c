/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:38:43 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/21 17:09:56 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	controller(t_args *args)
{
	uint64_t	i;

	i = 0;
	while (1)
	{
		i++;
		if (i == args->nb_ph)
			i = 0;
		if (!args->philos[i].is_eating && get_time_now() > \
args->philos[i].last_meal + args->time_to_die)
		{
			pthread_mutex_lock(&args->print_lock);
			printf("%llu %d died\n", get_time_now() - \
args->start_time, args->philos[i].id + 1);
			return (0);
		}
		if (args->ph_must_eat == args->nb_ph)
		{
			pthread_mutex_lock(&args->print_lock);
			return (0);
		}
		usleep(5);
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
}

int	create_thread(t_args *args, uint64_t limit, uint64_t p)
{
	while (p < limit)
	{
		if (pthread_create(&args->th[p], NULL, &philosopher, &args->philos[p]))
			return (printf("Issue in thread creation\n"));
			p += 2;
		usleep(1);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_args		args;

	if (!check_ac(ac, av, &args) || !check_av(ac, av) || \
!init_philos(ac, av, &args))
		return (-1);
	args.th = malloc(sizeof(pthread_t) * args.nb_ph);
	if (!args.th)
		return (-1);
	create_thread(&args, args.nb_ph, 0);
	create_thread(&args, args.nb_ph, 1);
	if (!controller(&args))
		return (free_all(&args, args.th));
	return (0);
}
