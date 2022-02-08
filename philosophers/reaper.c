/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:28:06 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/07 21:32:45 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo	*philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->data->death_lock);
	res = philo->data->philo_died;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (res);
}

int	check_stuffed(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].lock_stuffed);
		if (philo[i].nbr_eat != 0)
		{
			pthread_mutex_unlock(&philo[i].lock_stuffed);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].lock_stuffed);
		i++;
	}
	return (DONE);
}

void	ft_died(t_philo *philo)
{
	pthread_mutex_lock(&philo[0].data->death_lock);
	philo[0].data->philo_died = DEAD;
	pthread_mutex_unlock(&philo[0].data->death_lock);
}

void	ft_reaper(t_philo *philo)
{
	unsigned long	time;
	unsigned long	deathtime;
	int				i;

	i = 0;
	time = timestamp();
	ft_usleep(philo[0].data->die_time);
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&philo[i].lock_death);
		if (timestamp() - philo[i].last_meal > philo[i].data->die_time)
			ft_died(philo);
		pthread_mutex_unlock(&philo[i].lock_death);
		if (philo[i].data->philo_died == DEAD)
			break ;
		if (check_stuffed(&philo[i]) == DONE && philo->data->eat_limit != 0)
			return ;
		i++;
		if (i == philo[0].data->nbr_philo)
			i = 0;
	}
	usleep(1000);
	deathtime = timestamp() - time;
	printf("%ld	%d	died\n", deathtime, philo[i].philo_id);
}

void	create_reaper(pthread_t reaper, t_philo *philo, int i)
{
	while (i-- > 0)
		pthread_mutex_unlock(&philo[i].philo_lock);
	if (pthread_create(&reaper, NULL, (void *)(&ft_reaper),
		(void *)philo) != 0)
		write(2, "Can't create thread\n", 20);
	if (pthread_join(reaper, NULL) != 0)
		write(2, "Can't join thread\n", 18);
}
