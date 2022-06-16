/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:39:27 by lelhlami          #+#    #+#             */
/*   Updated: 2022/05/21 13:10:29 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define EXIT_DEAD 0
# define EXIT_FAILED 1
# define EXIT_MIN_EATING 2

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int				id;
	int				must_eat;
	uint64_t		last_meal;
	int				is_eating;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	t_philo		*philos;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	time_to_die;
	uint64_t	start_time;
	uint64_t	nb_ph;
	int			ph_must_eat;
	sem_t		*shopsticks;
	pid_t		*p;
	sem_t		*lock_print;
	int			dead;
}	t_args;

uint64_t	ft_atoi(const char *str);
void		init_philos(int ac, char **av, t_args *args);
void		init_args(int ac, char **av, t_args *args);
void		check_av(int ac, char **av);
int			ft_strlen(const char *s);
uint64_t	get_time_now(void);
void		free_all(t_args *args, pthread_t *th);
int			ft_strlen(const char *s);
int			check_out_nbr(unsigned long nbr, int neg);
void		eating_time(t_philo *philo);
void		thinking_time(t_philo *philo);
void		pick_shopstick(t_philo *philo);
void		leave_shopstick(t_philo *philo);
void		kill_all(t_args *args);
void		my_sleep(uint64_t pause, t_philo *philo);
void		wait_pid(t_args *args);
void		ft_check(t_philo *philo);

#endif
