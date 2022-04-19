/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:49:04 by lelhlami          #+#    #+#             */
/*   Updated: 2022/04/19 17:31:31 by lelhlami         ###   ########.fr       */
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

void	*init_philos(int ac, char **av, t_args *args)
{
	int i;
	int nbp;

	nbp = ft_atoi(av[1]);
	args->philos = (t_philo *)malloc(sizeof(t_philo) * nbp);
	args->shopsticks = (t_shopsticks *)malloc(sizeof(t_shopsticks) * nbp);
	args->nb_ph = nbp;
	if (!args->philos || !args->shopsticks)
		exit(0);
	i = -1;
	while (++i < nbp)
	{
		args->philos[i].id = i;
		args->philos[i].state = THINKING;
		args->philos[i].shopstick_r = (i + 1) % nbp;
		args->philos[i].shopstick_l = i;
		args->time_to_die = ft_atoi(av[2]);
		args->time_to_eat = ft_atoi(av[3]);
		args->time_to_sleep = ft_atoi(av[4]);
		args->philos[i].args = args;
		if(ac == 6)
			args->philos[i].must_eat = ft_atoi(av[5]);
		else 
			args->philos[i].must_eat = -1;
		args->shopsticks[i].free = 1;
		args->shopsticks[i].id = i;
		args->philos[i].last_meal = get_time_now();
		pthread_mutex_init(&args->shopsticks[i].lock, NULL);
		pthread_mutex_init(&args->philos[i].lock_state, NULL);
	}
	return (0);
}

int	get_time_now()
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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