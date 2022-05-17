/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:11:17 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/17 20:13:08 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(const char *s)
{
	uint64_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	free_all(t_args *args, pthread_t *th)
{
	uint64_t	i;

	i = -1;
	while (++i < args->nb_ph)
		pthread_mutex_destroy(&args->shopsticks[i]);
	pthread_mutex_destroy(&args->print_lock);
	free(args->shopsticks);
	i = -1;
	while (++i)
		pthread_detach(th[i]);
	free(args->philos);
	free(th);
	return (0);
}
