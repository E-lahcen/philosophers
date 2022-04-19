/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:38:43 by lelhlami          #+#    #+#             */
/*   Updated: 2022/04/19 18:49:37 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	 eating_time(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock_state);
    philo->last_meal = get_time_now();
    philo->must_eat--;
    philo->state = EATING;
    printf("%d\t%d is eating\n", get_time_now() - philo->args->start_time , philo->id + 1);
    pthread_mutex_unlock(&philo->lock_state);
    if (!philo->must_eat)
    {
        printf("%d\t%d died\n", get_time_now() - philo->args->start_time , philo->id + 1);
        exit(0);
    }
    usleep(philo->args->time_to_eat * 1000);
}

void	 thinking_time(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock_state);
    printf("%d\t%d is thinking\n", get_time_now() - philo->args->start_time , philo->id + 1);
    philo->state = THINKING;
    pthread_mutex_unlock(&philo->lock_state);
}

void    pick_shopstick(t_philo *philo)
{
    pthread_mutex_lock(&philo->args->shopsticks[philo->shopstick_l].lock);
    printf("%d\t%d has taken a fork\n", get_time_now() - philo->args->start_time , philo->id + 1);
    pthread_mutex_lock(&philo->args->shopsticks[philo->shopstick_r].lock);
    printf("%d\t%d has taken a fork\n", get_time_now() - philo->args->start_time , philo->id + 1);
}

void    leave_shopstick(t_philo *philo)
{
    pthread_mutex_unlock(&philo->args->shopsticks[philo->shopstick_l].lock);
    pthread_mutex_unlock(&philo->args->shopsticks[philo->shopstick_r].lock);
    printf("%d\t%d is sleeping\n", get_time_now() - philo->args->start_time , philo->id + 1);
    usleep(philo->args->time_to_sleep * 1000);
}

void	*philosopher(void *philo_arg)
{
	t_philo		*philo;

	philo = (t_philo*)philo_arg;
	while (1)
	{
        if (get_time_now() > philo->last_meal + philo->args->time_to_die)
        {
            printf("%d\t%d died\n", get_time_now() - philo->args->start_time , philo->id + 1);
            exit(0);
        }
		pick_shopstick(philo);
		eating_time(philo);
		leave_shopstick(philo);
        thinking_time(philo);
	}
}

int	main(int ac, char **av)
{
	pthread_t	*th;
    t_args      args;
	int			i;

	chek_av(ac, av);
    i = -1;
    init_philos(ac, av, &args);
    args.start_time = get_time_now();
    args.nb_ph = ft_atoi(av[1]);
    th = malloc(sizeof(pthread_t) * args.nb_ph);
    i = -1;
	while (++i < args.nb_ph)
	{
		if (pthread_create(&th[i], NULL, &philosopher, &args.philos[i]))
		{
			write(1, "Issue in thread creation\n", 25);
			exit(0);
		}
        usleep(100);
	}
    i = -1;
    while (++i < args.nb_ph)
        pthread_join(th[i], NULL);
    free(args.shopsticks);
    free(args.philos);
    free(th);
    return (0);
}
