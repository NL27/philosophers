/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALLNEW.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:11:32 by nlenoch           #+#    #+#             */
/*   Updated: 2022/01/20 23:27:51 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =========================HEADER FILE========================= */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define FORK 1
#define EAT 2
#define SLEEP 3
#define THINK 4
#define DEAD 5

typedef struct s_input
{
	int	nbr_philo;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	nbr_eat;
}	t_input;

typedef struct s_philo
{
	t_input			*data;
	int				philo_id;
	int				nbr_eat;
	int				dead;
	int				status;
	uint64_t		start_time;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_fork1;
	pthread_mutex_t	*lock_fork2;
	
}	t_philo;

// struct s_timeval
// {
// 	time_t		tv_sec;
// 	suseconds_t	tv_usec;
// }	t_timeval;

/* =========================ERROR HANDLING========================= */

int	ft_error(void)
{
	printf("%s", "Usage: ./philo [philo nbr] [dieTime] [eatTime] [sleepTime] ");
	printf("%s", "{nbr philos must eat}\n NO negative nbrs & only nbrs > 0!");
	return (-1);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if ((*str >= 33 && *str <= 47) || (*str >= 58 && *str <= 126))
		return (-1);
	while ((*str >= 48) && (*str <= 57))
	{
		result = (result * 10) + (*str - 48);
		str++;
	}
	return (sign * result);
}

int	check_args(int argc, char **argv)
{	
	int	n;
	int	i;
	int	j;

	n = argc;
	i = 1;
	j = 0;
	while (n-- != 1)
	{
		while (argv[i])
		{
			while (argv[i][j] != '\0')
			{
				if (ft_atoi(argv[i]) == -1)
					return (-1);
				j++;
			}
			i++;
		}
	}
	return (0);
}

int	error_check(t_input	data)
{
	if (data.nbr_philo == 0 || data.die_time == 0 || data.eat_time == 0
		|| data.sleep_time == 0 || data.nbr_eat == 0)
		return (-1);
	return (0);
}

/* =========================INSERT DATA========================= */

static t_input	insert_args(char **argv)
{
	t_input	data;

	if (argv[5])
		data.nbr_eat = ft_atoi(argv[5]);
	else
		data.nbr_eat = -1;
	data.nbr_philo = ft_atoi(argv[1]);
	data.die_time = ft_atoi(argv[2]);
	data.eat_time = ft_atoi(argv[3]);
	data.sleep_time = ft_atoi(argv[4]);
	return (data);
}

/* =========================GET TIME========================= */

uint64_t	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

uint64_t	ft_usleep(uint64_t timetoDoSmth)
{
	uint64_t	start;

	start = timestamp();
	while (timetoDoSmth > timestamp() - start)
		usleep(100);
	return (0);
}

/* =========================INITIALIZE PHILOS========================= */

t_philo	*init(t_input data)
{
	int		i;
	t_philo	*philo;

	philo = malloc((data.nbr_philo) * sizeof(pthread_t));
	while (i < data.nbr_philo)
	{
		philo[i].philo_id = i + 1;
		printf("We have a philo: %d\n", philo[i].philo_id);
		philo[i].nbr_eat = data.nbr_eat;
		philo->start_time = 0;
		philo->dead = 0;
		i++;
	}
	return (philo);
}

// void	ft_reaper(t_philo *philo, long time)
// {
// 	pthread_mutex_lock(&philo->lock_death);
// 	philo.dead = 1;
// 	pthread_mutex_unlock(&philo->lock_death);
// 	printf("%ld		%d	died\n", time, philo->philo_id);
// }

int	print(t_philo *philo)
{
	long	time;

	// pthread_mutex_lock(&philo.lock_print)
	if (philo->dead == 0)
	{
		time = timestamp() - philo->start_time;
		if (philo->status == FORK)
			printf("%ld		%d	has taken a fork\n", time, philo->philo_id);
		if (philo->status == EAT)
			printf("%ld		%d	is eating\n", time, philo->philo_id);
		if (philo->status == SLEEP)
			printf("%ld		%d	is sleeping\n", time, philo->philo_id);
		if (philo->status == THINK)
			printf("%ld		%d	is thinking\n", time, philo->philo_id);
		if (philo->status == DEAD)
		{
			// ft_reaper(philo, time);
			return (-1);
		}
	}
	return (0);
}

void *routine(t_philo *philo)
{
	// pthread_mutex_t	mutex;
	
	// if (philo->philo_id % 2 != 0)
	// 	 philo->status = SLEEP;
	// else
	// 	philo->status = THINK;
	// while (philo->nbr_eat != 0 && philo->dead == 0)
	// {
	// 	if (philo->status == THINK)
	// 		;
	// }

	printf("We have a thread: %d\n", philo->philo_id);
}                                                                                                                                                        

static	t_philo *create_threads(t_philo *philo, t_input data)
{
	int				i;
	pthread_t		*thread;
	pthread_mutex_t	mutex;

	i = 0;
	thread = malloc((data.nbr_philo) * sizeof(pthread_t));
	pthread_mutex_init(&mutex, NULL);
	printf("Nbr of Philos: %d\n", data.nbr_philo);
	while (i < data.nbr_philo)
	{
		if (pthread_create(&thread[i], NULL, &routine,
				(void *)&philo[i]) != 0)
			write(2, "Can't create thread\n", 20);
		printf("Thread %d has started\n", i);
		i++;
		// printf("Philo %d has started\n", philo[i].philo_id);
	}
	while (i-- > 0)
	{
		if (pthread_join(thread[i], NULL) != 0)
			write(2, "Can't join thread\n", 18);
		printf("Thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	// printf("Number of philos: %d", nbr);
	return (philo);
}

int	main(int argc, char **argv)
{
	t_input	data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (ft_error());
	if (check_args(argc, argv) == -1)
		return (ft_error());
	else if (check_args(argc, argv) != -1)
		data = insert_args(argv);
	if (error_check(data) == -1)
		return (ft_error());
	philo = init(data);
	philo = create_threads(philo, data);
	// printf("%d\n", data.nbr_philo);
	// printf("%d\n", data.die_time);
	// printf("%d\n", data.eat_time);
	// printf("%d\n", data.sleep_time);
	// printf("%d\n", data.nbr_eat);
	return (0);
}
