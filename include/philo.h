/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:39:27 by lelhlami          #+#    #+#             */
/*   Updated: 2022/04/12 12:26:51 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define THREAD_NB 5
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define HUNGRY 3

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_philo
{
    int state;
    int id;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
}   t_philo;

int	    ft_atoi(const char *str);
void	init_philo(char **av, t_philo *philo);
void	chek_av(int ac, char **av);
int	    ft_strlen(const char *s);
t_philo	*alloc_it(int size);

#endif