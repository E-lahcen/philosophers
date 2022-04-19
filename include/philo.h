/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:39:27 by lelhlami          #+#    #+#             */
/*   Updated: 2022/04/19 18:04:56 by lelhlami         ###   ########.fr       */
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
#include <sys/time.h>

typedef struct s_philo
{
    int             id;
    int             state;
    int             shopstick_l;
    int             shopstick_r;
    int             must_eat;
    int             last_meal;
    pthread_mutex_t lock_state;
    struct s_args   *args;
}   t_philo;

typedef struct s_shopsticks
{
    pthread_mutex_t lock;
    int id;
    int free;
} t_shopsticks;

typedef struct s_args
{
    t_philo         *philos;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_die;
    int             start_time;
    int             nb_ph;
    int             current_ph;
    t_shopsticks    *shopsticks;
} t_args;

int	            ft_atoi(const char *str);
void	        *init_philos(int ac, char **av, t_args *args);
void	        chek_av(int ac, char **av);
int	            ft_strlen(const char *s);
int 	        get_time_now();

#endif