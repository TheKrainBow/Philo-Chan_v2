/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:27:23 by krain             #+#    #+#             */
/*   Updated: 2021/11/13 17:27:41 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_data(t_data *d, char **av)
{
	int		i;

	d->n_philos = ft_atoi(av[0]);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->n_philos);
	d->p = malloc(sizeof(t_philo) * d->n_philos);
	i = -1;
	while (++i < d->n_philos)
	{
		pthread_mutex_init(d->forks + i, NULL);
		pthread_mutex_init(&d->p[i].mutex_task, NULL);
		pthread_mutex_init(&d->p[i].mutex_eat, NULL);
		pthread_mutex_init(&d->p[i].mutex_exit, NULL);
		pthread_mutex_init(&d->p[i].mutex_angel, NULL);
	}
	pthread_mutex_init(&d->mic, NULL);
	d->philos_threads = malloc(sizeof(pthread_t) * d->n_philos);
	d->t_die = ft_atoi(av[1]);
	d->t_eat = ft_atoi(av[2]);
	d->t_sleep = ft_atoi(av[3]);
}

void	free_data(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philos)
	{
		pthread_mutex_destroy(d->forks + i);
		pthread_mutex_destroy(&d->p[i].mutex_task);
		pthread_mutex_destroy(&d->p[i].mutex_eat);
		pthread_mutex_destroy(&d->p[i].mutex_angel);
		pthread_mutex_destroy(&d->p[i].mutex_exit);
	}
	pthread_mutex_unlock(&d->mic);
	pthread_mutex_destroy(&d->mic);
	free(d->p);
	free(d->forks);
	free(d->philos_threads);
	free(d);
}

void	set_forks(t_data *d, int i)
{
	if (d->p[i].id % 2)
	{
		d->p[i].l_fork = d->forks + i;
		if (i < d->n_philos - 1)
			d->p[i].r_fork = d->forks + i + 1;
		else
			d->p[i].r_fork = d->forks;
	}
	else
	{
		d->p[i].r_fork = d->forks + i;
		if (i < d->n_philos - 1)
			d->p[i].l_fork = d->forks + i + 1;
		else
			d->p[i].l_fork = d->forks;
	}
}

void	start_simulation(t_data *d)
{
	int		i;
	long	starting_time;

	starting_time = ft_time(0);
	i = -1;
	while (++i < d->n_philos)
	{
		d->p[i].id = i + 1;
		d->p[i].task = THINK;
		d->p[i].t_die = d->t_die;
		d->p[i].t_sleep = d->t_sleep;
		d->p[i].t_eat = d->t_eat;
		d->p[i].n_meals = 0;
		d->p[i].max_meals = d->max_meals;
		d->p[i].exited = 0;
		d->p[i].mic = &d->mic;
		set_forks(d, i);
		d->p[i].sim_start = starting_time;
		d->p[i].t_start = ft_time(0);
		d->p[i].t_last_eat = 0;
		d->p[i].angel = 0;
	}
	i = -1;
	while (++i < d->n_philos)
	{
		pthread_create(d->philos_threads + i, NULL, philo_chan, d->p + i);
		pthread_detach(d->philos_threads[i]);
		pthread_create(&d->p[i].death_angel, NULL, philo_angel, d->p + i);
		pthread_detach(d->p[i].death_angel);
	}
}
