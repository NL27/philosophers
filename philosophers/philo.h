/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:53:30 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/07 19:57:36 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define	PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DONE 5
# define DEAD 666

typedef struct s_input
{
	int				nbr_philo;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	int				nbr_eat;
	int				eat_limit;
	int				philo_died;
	int				philo_started;
	pthread_mutex_t	universal_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*forks;
}	t_input;

typedef struct s_philo
{
	t_input			*data;
	int				philo_id;
	int				nbr_eat;
	int				status;
	unsigned long	init_time;
	unsigned long	last_meal;
	pthread_mutex_t	lock_stuffed;
	pthread_mutex_t	philo_lock;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}	t_philo;

struct s_timeval
{
	time_t		tv_sec;
	suseconds_t	tv_usec;
}	t_timeval;

int				ft_error(void);
int				error_check(t_input	*data);
int				ft_atoi(const char *str);
int				check_args(int argc, char **argv);
void			insert_args(char **argv, t_input *data);
unsigned long	timestamp(void);
void			create_threads(t_philo *philo, t_input *data);
void			ft_usleep(unsigned long timetodoSmth);
int				print_status(t_philo *philo);
void			*routine(t_philo *philo);
int				philo_died(t_philo *philo);
int				check_death(t_philo	*philo);
void			create_reaper(pthread_t reaper, t_philo *philo, int i);
int				check_stuffed(t_philo *philo);

#endif