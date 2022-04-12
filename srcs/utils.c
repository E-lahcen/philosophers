/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:49:04 by lelhlami          #+#    #+#             */
/*   Updated: 2022/04/12 12:26:40 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	check_out_nbr(unsigned long nbr, int neg)
{
	if (nbr > 9223372036854775807)
	{
		if (neg == 1)
			return (-1);
		else if (neg == -1)
			return (0);
	}
	return (nbr * neg);
}

int	ft_atoi(const char *str)
{
	unsigned long			nbr;
	int						is_negative;

	nbr = 0;
	is_negative = 1;
	while ((*str == ' ' || *str == '\t' || *str == '\n' || *str
			== '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		is_negative = -1;
	}
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			nbr = nbr * 10 + (*str - 48);
		else
			return (is_negative * nbr);
		str++;
	}
	return (check_out_nbr(nbr, is_negative));
}

void	init_philo(char **av, t_philo *philo)
{
	int nb;
	int i;

	nb = ft_atoi(av[1]);
	i = -1;
	while (++i < nb)
	{
		philo[i].id = i;
		philo[i].state = THINKING;
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
	}
}

t_philo	*alloc_it(int size)
{
	t_philo *philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * size);
	if (!philo)
	{
		write(1, "Issue in memory allocation\n", 28);
		exit(0);
	}
	return (philo);
}

void	chek_av(int ac, char **av)
{
	int len;
	int i;
	int j;

	if (ac < 5 || ac > 6)
	{
		write(1, "Issue in number of arguments!\nPlease provide : number_of_philosophers | time_to_die | time_to_eat | time_to_sleep\n", 114);
		exit(0);
	}
	i = 0;
	while (++i < ac)
	{
		len = ft_strlen(av[i]);
		j = -1;
		while (++j < len)
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				write(1, "Issue in arguments!\nPlease provide : number_of_philosophers | time_to_die | time_to_eat | time_to_sleep\n", 114);
				exit(0);
			}
		}
	}
}