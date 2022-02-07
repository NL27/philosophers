/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:45:39 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/07 21:00:09 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_mutex(t_input *data)
{
	pthread_mutex_init(&data->universal_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
}

void	end_mutex(t_input *data)
{
	pthread_mutex_destroy(&data->universal_lock);
	pthread_mutex_destroy(&data->death_lock);
}

void	create_threads(t_philo *philo, t_input *data)
{
	int				i;
	pthread_t		*thread;
	pthread_t		reaper;

	i = 0;
	reaper = (pthread_t) NULL;
	thread = malloc((data->nbr_philo) * sizeof(pthread_t));
	start_mutex(data);
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].philo_lock);
		if (pthread_create(&thread[i], NULL, (void *)(routine),
			(void *)(&philo[i])) != 0)
			write(2, "Can't create thread\n", 20);
		i++;
	}
	create_reaper(reaper, philo, i);
	while (i-- > 0)
	{
		if (pthread_join(thread[i], NULL) != 0)
			write(2, "Can't join thread\n", 18);
	}
	end_mutex(data);
	free(thread);
	thread = NULL;
}
