/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:38:43 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/21 20:58:38 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	*controller(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!philo->args->dead)
	{
		ft_check(philo);
		if (philo->args->nb_ph > 10)
			usleep(100);
		usleep(100);
	}
	return (NULL);
}

void	*philosopher(t_args *args, int i)
{
	pthread_t	th;

	pthread_create(&th, NULL, &controller, &args->philos[i]);
	while (!args->dead && args->philos[i].must_eat)
	{
		pick_shopstick(&args->philos[i]);
		eating_time(&args->philos[i]);
		leave_shopstick(&args->philos[i]);
		thinking_time(&args->philos[i]);
	}
	pthread_detach(th);
	exit(1);
}

void	kill_all(t_args *args)
{
	uint64_t	i;

	i = -1;
	while (++i < args->nb_ph && args->p[i] != 0)
		kill(args->p[i], 9);
	free(args->philos);
	free(args->p);
}

void	wait_pid(t_args *args)
{
	uint64_t	i;
	int			status;

	i = -1;
	status = 0;
	while (++i < args->nb_ph)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
		{
			kill_all(args);
			exit(0);
		}
	}
}

int	main(int ac, char **av)
{
	t_args		args;
	uint64_t	i;

	check_av(ac, av);
	init_philos(ac, av, &args);
	args.p = malloc(sizeof(pid_t *) * args.nb_ph);
	if (!args.p)
		exit(EXIT_FAILED);
	args.start_time = get_time_now();
	i = -1;
	while (++i < args.nb_ph)
	{
		args.p[i] = fork();
		if (args.p[i] < 0)
			exit(EXIT_FAILED);
		if (args.p[i] == 0)
			philosopher(&args, i);
	}
	wait_pid(&args);
	return (0);
}
