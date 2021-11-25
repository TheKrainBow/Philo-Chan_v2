/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:04:23 by krain             #+#    #+#             */
/*   Updated: 2021/11/13 17:20:35 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	*philo_angel(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	while (get_task(&philo->task, &philo->mutex_task) != DEAD)
	{
		if (philo->t_die + get_long(&philo->t_last_eat, &philo->mutex_eat)
			< ft_time(philo->t_start))
			set_task(&philo->task, &philo->mutex_task, DEAD);
		usleep(100);
	}
	set_long(&philo->angel, &philo->mutex_angel, 0);
	return (NULL);
}

void	ft_talk(t_philo *philo, char *str, long time)
{
	pthread_mutex_lock(philo->mic);
	if (get_task(&philo->task, &philo->mutex_task) != DEAD)
		printf("%5ld  %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->mic);
}

void	ft_eat(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(philo->l_fork);
	ft_talk(philo, "has taken a fork", ft_time(philo->sim_start));
	pthread_mutex_lock(philo->r_fork);
	if (get_task(&philo->task, &philo->mutex_task) == DEAD)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	ft_talk(philo, "has taken a fork", ft_time(philo->sim_start));
	ft_talk(philo, "is eating", ft_time(philo->sim_start));
	if (get_task(&philo->task, &philo->mutex_task) == DEAD)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	set_task(&philo->task, &philo->mutex_task, EAT);
	meals = get_long(&philo->n_meals, &philo->mutex_eat);
	set_long(&philo->n_meals, &philo->mutex_eat, meals + 1);
	set_long(&philo->t_last_eat, &philo->mutex_eat, ft_time(philo->t_start));
	ft_usleep(philo->t_eat, philo);
}

void	ft_sleep(t_philo *philo)
{
	if (get_task(&philo->task, &philo->mutex_task) == DEAD)
		return ;
	ft_talk(philo, "is sleeping", ft_time(philo->sim_start));
	if (get_task(&philo->task, &philo->mutex_task) == DEAD)
		return ;
	set_task(&philo->task, &philo->mutex_task, SLEEP);
	ft_usleep(philo->t_sleep, philo);
	ft_talk(philo, "is thinking", ft_time(philo->sim_start));
	if (get_task(&philo->task, &philo->mutex_task) == DEAD)
		return ;
	set_task(&philo->task, &philo->mutex_task, THINK);
}

void	*philo_chan(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	while (get_task(&philo->task, &philo->mutex_task) != DEAD)
	{
		ft_eat(philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		ft_sleep(philo);
	}
	set_long(&philo->exited, &philo->mutex_exit, 0);
	return (NULL);
}
