/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:39:27 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/17 19:40:08 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				shopstick_l;
	int				shopstick_r;
	int				must_eat;
	uint64_t		last_meal;
	int				is_eating;
	pthread_mutex_t	lock_controller;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	t_philo			*philos;
	pthread_t		*th;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		time_to_die;
	uint64_t		start_time;
	uint64_t		nb_ph;
	uint64_t		ph_must_eat;
	pthread_mutex_t	*shopsticks;
	pthread_mutex_t	print_lock;
}	t_args;

uint64_t	ft_atoi(const char *str);
int			init_philos(int ac, char **av, t_args *args);
void		init_args(char **av, t_args *args);
int			check_av(int ac, char **av);
int			ft_strlen(const char *s);
uint64_t	get_time_now(void);
int			free_all(t_args *args, pthread_t *th);
void		leave_shopstick(t_philo *philo);
void		pick_shopstick(t_philo *philo);
void		thinking_time(t_philo *philo);
void		eating_time(t_philo *philo);
int			time_sleep_checker(t_philo *philo, int loop);
void		my_sleep(uint64_t pause);
int			check_ac(int ac, char **av, t_args *args);

#endif
