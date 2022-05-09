/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:39:27 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/09 11:53:29 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				shopstick_l;
	int				shopstick_r;
	int				must_eat;
	int				last_meal;
	int				is_eating;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	t_philo			*philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				start_time;
	int				nb_ph;
	int				ph_must_eat;
	pthread_mutex_t	*shopsticks;
}	t_args;

int		ft_atoi(const char *str);
void	init_philos(int ac, char **av, t_args *args);
void	init_args(char **av, t_args *args);
void	chek_av(int ac, char **av);
int		ft_strlen(const char *s);
int		get_time_now(void);
void	free_all(t_args *args, pthread_t *th);
void	leave_shopstick(t_philo *philo);
void	pick_shopstick(t_philo *philo);
void	thinking_time(t_philo *philo);
void	eating_time(t_philo *philo);
int		check_out_nbr(unsigned long nbr, int neg);
void	time_sleep_checker(t_philo *philo);

#endif
