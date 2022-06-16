/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:39:17 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/21 15:43:09 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	eating_time(t_philo *philo)
{
	uint64_t	time;

	philo->is_eating = 1;
	sem_wait(philo->args->lock_print);
	philo->last_meal = get_time_now();
	philo->must_eat--;
	time = get_time_now() - philo->args->start_time;
	printf("%llu %d is eating\n", time, philo->id + 1);
	sem_post(philo->args->lock_print);
	philo->is_eating = 0;
	my_sleep(philo->args->time_to_eat, philo);
	if (!philo->must_eat)
		philo->args->dead = 1;
}

void	thinking_time(t_philo *philo)
{
	uint64_t	time;

	sem_wait(philo->args->lock_print);
	time = get_time_now() - philo->args->start_time;
	printf("%llu %d is thinking\n", time, philo->id + 1);
	sem_post(philo->args->lock_print);
}

void	pick_shopstick(t_philo *philo)
{
	uint64_t	time;

	sem_wait(philo->args->shopsticks);
	sem_wait(philo->args->lock_print);
	time = get_time_now() - philo->args->start_time;
	printf("%llu %d has taken a fork\n", time, philo->id + 1);
	sem_post(philo->args->lock_print);
	sem_wait(philo->args->shopsticks);
	sem_wait(philo->args->lock_print);
	time = get_time_now() - philo->args->start_time;
	printf("%llu %d has taken a fork\n", time, philo->id + 1);
	sem_post(philo->args->lock_print);
}

void	leave_shopstick(t_philo *philo)
{
	uint64_t	time;

	sem_post(philo->args->shopsticks);
	sem_post(philo->args->shopsticks);
	sem_wait(philo->args->lock_print);
	time = get_time_now() - philo->args->start_time;
	printf("%llu %d is sleeping\n", time, philo->id + 1);
	sem_post(philo->args->lock_print);
	my_sleep(philo->args->time_to_sleep, philo);
}

void	my_sleep(uint64_t pause, t_philo *philo)
{
	uint64_t	time;

	time = get_time_now();
	while (get_time_now() < time + pause)
	{
		ft_check(philo);
		usleep(50);
	}
}
