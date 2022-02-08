/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:40:29 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/08 11:50:24 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	return (0);
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
	if (result > 2147483647 || result < 0)
		return (-1);
	return (sign * result);
}

int	check_args(int argc, char **argv)
{	
	int	n;
	int	i;
	int	j;

	n = argc;
	i = 1;
	while (n-- != 1)
	{
		while (argv[i])
		{
			j = 0;
			if (ft_atoi(argv[i]) == -1)
				return (-1);
			while (argv[i][j] != '\0')
			{
				if (ft_isdigit(argv[i][j]) == 0)
					return (-1);
				j++;
			}
			i++;
		}
	}
	return (0);
}

int	error_check(t_input	*data)
{
	if (data->nbr_philo == 0 || data->die_time == 0 || data->eat_time == 0
		|| data->sleep_time == 0 || data->nbr_eat == 0)
		return (-1);
	return (0);
}

void	insert_args(char **argv, t_input *data)
{
	data->eat_limit = 1;
	if (argv[5])
		data->nbr_eat = ft_atoi(argv[5]);
	else
	{
		data->nbr_eat = -1;
		data->eat_limit = 0;
	}
	data->nbr_philo = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->philo_died = 0;
}
