/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:38:43 by lelhlami          #+#    #+#             */
/*   Updated: 2022/04/12 12:33:06 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t lock[2];

void    sleeping_time(int i)
{
    printf("I am sleeping  %d\n", i);
}

void	 eating_time(int i)
{
    printf("I am eating  %d\n", i);
}

void	 thinking_time(int i)
{
    printf("I am thinking %d\n", i);
}

void    pick_shopstick(int i)
{
    pthread_mutex_lock(&lock[0]);
    pthread_mutex_unlock(&lock[0]);
    pthread_mutex_lock(&lock[1]);
    printf("I am picking shopstick %d\n", i);
}

void    leave_shoptick(int i)
{
    printf("Leaving shopstick %d\n", i);
}

void    philosopher(void *arg)
{
    t_philo *philo;

    philo = (t_philo*)arg;
}

int	main(int ac, char **av)
{
	pthread_t	*th;
    t_philo     *philo;
    int         i;
    int         nb_philo;

	chek_av(ac, av);
    nb_philo = ft_atoi(av[1]);
    philo = alloc_it(nb_philo);
    init_philo(av, philo);
    i = -1;
    th = (pthread_t *)malloc(sizeof(pthread_t) * nb_philo);
    if (!th)
	{
		write(1, "Issue in memory allocation\n", 28);
		exit(0);
	}
    i = -1;
    while (++i < nb_philo)
        if (pthread_create(&th[i], NULL, (void *)&philosopher, philo))
        {
            write(1, "Issue in thread creation\n", 25);
            exit(0);
        }
    i = -1;
    while (++i < nb_philo)
    {
        if (pthread_join(th[i], NULL))
        {
            write(1, "Issue in thread joining\n", 25);
            exit(0);
        }
    }
    free(philo);
    // system("leaks philo");
    return (0);
}
