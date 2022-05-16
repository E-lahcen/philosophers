/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:11:17 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/16 13:03:44 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int ft_strlen(const char *s)
{
	uint64_t i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

uint64_t ft_atoi(const char *str)
{
	uint64_t nbr;

	nbr = 0;
	while ((*str == ' ' || *str == ' ' || *str == '\n' || *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - 48);
		if (nbr > LONG_MAX)
		{
			printf("Please provide a reasonable number asat!\n");
			exit(0);
		}
		str++;
	}
	return (nbr);
}

void check_av(int ac, char **av)
{
	int	len;
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("Issue in arguments!\nPlease provide : number_of_philosophers |\
time_to_die | time_to_eat | time_to_sleep\n");
		exit(0);
	}
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
				printf("Issue in arguments!\nPlease provide : number_of_philosophers |\
time_to_die | time_to_eat | time_to_sleep\n");
				exit(0);
			}
		}
	}
}
