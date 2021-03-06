/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:43:07 by magostin          #+#    #+#             */
/*   Updated: 2021/11/25 12:43:10 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_strisint(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * neg);
}

long	ft_time(long base_time)
{
	struct timeval	current_time;
	long			dest;

	gettimeofday(&current_time, NULL);
	dest = (current_time.tv_sec * 1000 + (current_time.tv_usec / 1000));
	return (dest - base_time);
}

void	ft_usleep(long us, t_philo *philo)
{
	long	objectif;

	objectif = ft_time(0) + us;
	while (ft_time(0) < objectif
		&& get_task(&philo->task, &philo->mutex_task) != DEAD)
	{
		usleep(100);
	}
}
