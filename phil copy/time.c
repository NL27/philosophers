/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:54:41 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/02 11:54:46 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_usleep(unsigned long timetodoSmth)
{
	unsigned long	start;

	start = timestamp();
	while (start + timetodoSmth > timestamp())
		usleep(100);
}
