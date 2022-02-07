/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:44:47 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/07 22:15:20 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	philo->status = FORK;
	print_status(philo);
	if (philo->data->nbr_philo == 1 && !pthread_mutex_unlock(philo->fork1))
		return (0);
	pthread_mutex_lock(philo->fork2);
	print_status(philo);
	philo->status = EAT;
	print_status(philo);
	ft_usleep(philo->data->eat_time);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_lock(&philo->lock_stuffed);
	if (philo->nbr_eat != -1)
		philo->nbr_eat = philo->nbr_eat - 1;
	pthread_mutex_unlock(&philo->lock_stuffed);
	return (1);
}

void	init_philostatus(t_philo *philo)
{
	if (philo->philo_id % 2 != 0 && philo->data->nbr_philo != 1)
	{
		philo->status = SLEEP;
		usleep(philo->data->nbr_philo * 10);
	}
	else
		philo->status = THINK;
}

void	*routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->init_time = timestamp();
	pthread_mutex_unlock(&philo->philo_lock);
	init_philostatus(philo);
	while (philo->nbr_eat != 0 && check_death(philo) != DEAD)
	{
		if (philo->status == THINK)
			philo->status = FORK;
		if (philo->status == FORK && !eat(philo))
			return (NULL);
		if (philo->nbr_eat == 0 || check_death(philo) == DEAD)
			return (NULL);
		if (philo->status == EAT)
		{
			philo->status = SLEEP;
			print_status(philo);
			ft_usleep(philo->data->sleep_time);
		}
		if (philo->status == SLEEP)
		{
			philo->status = THINK;
			print_status(philo);
		}
	}
	return (NULL);
}
