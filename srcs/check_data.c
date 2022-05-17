/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:57:33 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/17 19:37:53 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

uint64_t	ft_atoi(const char *str)
{
	uint64_t	nbr;

	nbr = 0;
	while ((*str == ' ' || *str == ' ' || *str == '\n' || \
*str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - 48);
		if (nbr > LONG_MAX)
			return (0);
		str++;
	}
	return (nbr);
}

int	check_ac(int ac, char **av, t_args *args)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf("Issue in arguments!\nPlease provide : number_of_philosophers |\
time_to_die | time_to_eat | time_to_sleep\n");
		return (0);
	}
	args->nb_ph = ft_atoi(av[1]);
	if (args->nb_ph > 1000 || !args->nb_ph)
	{
		printf("Wrong number of philosophers.\n");
		return (0);
	}
	i = 0;
	while (++i < 5)
	{
		if (!ft_atoi(av[i]))
			return (0 * printf("Please provide a reasonable number asat!\n"));
	}
	args->start_time = get_time_now();
	return (1);
}

int	check_av(int ac, char **av)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		len = ft_strlen(av[i]);
		j = -1;
		if (!len)
			len = 1;
		while (++j < len)
		{
			if (av[i][j] < '0' || av[i][j] > '9' || !av[i][0])
			{
				return (0 * printf("Issue in arguments!\nPlease provide : number_of_philosophers |\
time_to_die | time_to_eat | time_to_sleep\n"));
			}
		}
	}
	return (1);
}
