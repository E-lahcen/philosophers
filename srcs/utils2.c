/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:57:48 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/19 13:10:17 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating_time(t_philo *philo)
{
	uint64_t	time;

	philo->is_eating = 1;
	philo->last_meal = get_time_now();
	philo->must_eat--;
	time = get_time_now() - philo->args->start_time;
	pthread_mutex_lock(&philo->args->print_lock);
	printf("%llu %d is eating\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->args->print_lock);
	my_sleep(philo->args->time_to_eat);
	philo->is_eating = 0;
	if (!philo->must_eat)
	{
		philo->args->ph_must_eat++;
		philo->must_eat--;
	}
}

void	thinking_time(t_philo *philo)
{
	uint64_t	time;

	time = get_time_now() - philo->args->start_time;
	pthread_mutex_lock(&philo->args->print_lock);
	printf("%llu %d is thinking\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->args->print_lock);
}

void	pick_shopstick(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->args->shopsticks[philo->shopstick_l]);
	time = get_time_now() - philo->args->start_time;
	pthread_mutex_lock(&philo->args->print_lock);
	printf("%llu %d has taken a fork\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->args->print_lock);
	pthread_mutex_lock(&philo->args->shopsticks[philo->shopstick_r]);
	time = get_time_now() - philo->args->start_time;
	pthread_mutex_lock(&philo->args->print_lock);
	printf("%llu %d has taken a fork\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->args->print_lock);
}

void	leave_shopstick(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_unlock(&philo->args->shopsticks[philo->shopstick_l]);
	pthread_mutex_unlock(&philo->args->shopsticks[philo->shopstick_r]);
	time = get_time_now() - philo->args->start_time;
	pthread_mutex_lock(&philo->args->print_lock);
	printf("%llu %d is sleeping\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->args->print_lock);
	my_sleep(philo->args->time_to_sleep);
}
