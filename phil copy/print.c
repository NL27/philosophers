/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:52:18 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/07 18:46:21 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eat(t_philo *philo)
{
	printf("%lu	%d	is eating\n",
		timestamp() - philo->init_time, philo->philo_id);
	pthread_mutex_lock(&philo->lock_death);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->lock_death);
}

int	print_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->universal_lock);
	if (check_death(philo) != DEAD)
	{
		if (philo->status == FORK)
			printf("%lu	%d	has taken a fork\n",
				timestamp() - philo->init_time, philo->philo_id);
		if (philo->status == EAT)
			print_eat(philo);
		if (philo->status == SLEEP)
		{
			printf("%lu	%d	is sleeping\n",
				timestamp() - philo->init_time, philo->philo_id);
		}
		if (philo->status == THINK)
			printf("%lu	%d	is thinking\n",
				timestamp() - philo->init_time, philo->philo_id);
	}
	pthread_mutex_unlock(&philo->data->universal_lock);
	return (0);
}
