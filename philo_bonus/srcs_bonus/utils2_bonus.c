/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:57:48 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/17 20:17:48 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	free_all(t_args *args, pthread_t *th)
{
	free(args->shopsticks);
	free(args->philos);
	free(th);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

uint64_t	ft_atoi(const char *str)
{
	uint64_t	nbr;

	nbr = 0;
	while ((*str == ' ' || *str == ' ' || *str == '\n' || *str
			== '\r' || *str == '\v' || *str == '\f'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - 48);
		if (nbr > __LONG_MAX__ || !nbr)
			exit(printf("Issue in number of philosophers!\n"));
		str++;
	}
	return (nbr);
}

void	check_av(int ac, char **av)
{
	int	len;
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("Issue in number of arguments!\nPlease provide : number_of_philosophers \
| time_to_die | time_to_eat | time_to_sleep\n");
		exit(0);
	}
	i = 0;
	while (++i < ac)
	{
		len = ft_strlen(av[i]);
		j = -1;
		while (++j < len || !len)
		{
			if (av[i][j] < '0' || av[i][j] > '9' || !av[i][0])
			{
				printf("Issue in number of arguments!\nPlease provide : number_of_philosophers \
| time_to_die | time_to_eat | time_to_sleep\n");
				exit(0);
			}
		}
	}
}
