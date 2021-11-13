/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:04:23 by krain             #+#    #+#             */
/*   Updated: 2021/11/13 17:10:57 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	*philo_angel(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	while (get_task(&philo->task, &philo->mutex_task) != DEAD)
		if (ft_time(philo->t_start) - get_long(&philo->t_last_eat, &philo->mutex_eat) > philo->t_die)
			set_task(&philo->task, &philo->mutex_task, DEAD);
	set_long(&philo->angel, &philo->mutex_angel, 1);
	return (NULL);
}

void	ft_talk(t_philo *philo, char *str)
{
	if (get_task(&philo->task, &philo->mutex_task) == DEAD)
		return ;
	pthread_mutex_lock(philo->mic);
	printf("%ld\t%d %s\n", ft_time(philo->sim_start), philo->id, str);
	pthread_mutex_unlock(philo->mic);
	printf(WHITE);
}

void	ft_eat(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(philo->l_fork);
	ft_talk(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	if (get_task(&philo->task, &philo->mutex_task) == DEAD)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	ft_talk(philo, "has taken a fork");
	ft_talk(philo, "is eating");
	set_task(&philo->task, &philo->mutex_task, EAT);
	meals = get_long(&philo->n_meals, &philo->mutex_eat);
	set_long(&philo->n_meals, &philo->mutex_eat, meals + 1);
	set_long(&philo->t_last_eat, &philo->mutex_eat, ft_time(philo->t_start));
	ft_usleep(philo->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_sleep(t_philo *philo)
{
	if (get_task(&philo->task, &philo->mutex_task) == DEAD)
		return ;
	ft_talk(philo, "is sleeping");
	ft_usleep(philo->t_sleep);
	ft_talk(philo, "is thinking");
}

void	*philo_chan(void *p)
{
	t_philo			*philo;
	pthread_t		death_angel;
	t_task			task;

	philo = (t_philo *)p;
	philo->t_start = ft_time(0);
	philo->t_last_eat = 0;
	philo->angel = 0;
	task = THINK;
	pthread_create(&death_angel, NULL, philo_angel, philo);
	pthread_detach(death_angel);
	while (get_task(&philo->task, &philo->mutex_task) != DEAD)
	{
		ft_eat(philo);
		ft_sleep(philo);
	//	usleep(100);
	}
	set_long(&philo->exited, &philo->mutex_exit, 1);
	//printf("Philo %d exit thread\n", philo->id);
	return (NULL);
}