/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:55:28 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/08 11:45:45 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(void)
{
	printf("%s", "Usage: ./philo [philo nbr] [dieTime] [eatTime] [sleepTime] ");
	printf("%s", "{nbr philos must eat}\n NO negative nbrs & only int nbrs > 0");
	return (-1);
}

void	init_mutex(t_philo **philo, int i)
{
	pthread_mutex_init(&(*philo)[i].lock_death, NULL);
	pthread_mutex_init(&(*philo)[i].lock_stuffed, NULL);
	pthread_mutex_init(&(*philo)[i].philo_lock, NULL);
}

void	init_forks(t_input *data, int nbr)
{
	int	i;

	i = 0;
	while (nbr > i)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

t_philo	*init(t_input *data)
{
	int				i;
	static t_philo	*philos;

	i = 0;
	philos = malloc((data->nbr_philo) * sizeof(t_philo));
	data->forks = malloc((data->nbr_philo) * sizeof(pthread_mutex_t));
	init_forks(data, data->nbr_philo);
	while (i < data->nbr_philo)
	{
		philos[i].philo_id = i + 1;
		philos[i].fork1 = &data->forks[i];
		if (i == 0)
			philos[0].fork2 = &data->forks[data->nbr_philo - 1];
		else
			philos[i].fork2 = &data->forks[i - 1];
		philos[i].nbr_eat = data->nbr_eat;
		philos[i].last_meal = 0;
		philos[i].status = 0;
		philos[i].data = data;
		init_mutex(&philos, i);
		i++;
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	t_input	data;
	t_philo	*philos;

	philos = NULL;
	if (argc < 5 || argc > 6)
		return (ft_error());
	if (check_args(argc, argv) == -1)
		return (ft_error());
	else if (check_args(argc, argv) != -1)
		insert_args(argv, &data);
	if (error_check(&data) == -1)
		return (ft_error());
	philos = init(&data);
	create_threads(philos, &data);
	return (0);
}
	// system("leaks philo");
