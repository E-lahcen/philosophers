/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:38:43 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/09 11:54:54 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	controller(void *arg)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)arg;
	while (1)
	{
		// pthread_mutex_lock(&philo->lock_state);
		if (!philo->is_eating && get_time_now() > philo->last_meal + philo->args->time_to_die)
		{
			time = get_time_now() - philo->args->start_time;
			printf("%d %d died\n", time, philo->id + 1);
			// pthread_mutex_unlock(&philo->lock_state);
			exit(0);
		}
		// pthread_mutex_unlock(&philo->lock_state);
		time_sleep_checker(philo);
	}
}

void	*philosopher(void *philo_arg)
{
	t_philo		*philo;
	pthread_t	th;

	if (pthread_create(&th, NULL, (void *)&controller, philo_arg))
		exit(0);
	pthread_detach(th);
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
	int			i;

	chek_av(ac, av);
	args.nb_ph = ft_atoi(av[1]);
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
		time_sleep_checker(&args.philos[i]);
	}
	i = -1;
	while (++i < args.nb_ph)
		pthread_join(th[i], NULL);
	free_all(&args, th);
	return (0);
}
