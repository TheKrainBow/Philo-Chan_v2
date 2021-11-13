/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:19:33 by krain             #+#    #+#             */
/*   Updated: 2021/11/13 17:12:41 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_usleep(long us)
{
	long	objectif;
	long	ts;

	ts = ft_time(0);
	objectif = ts + us;
	while (ts < objectif)
	{
		usleep(10);
		ts = ft_time(0);
	}
}

int	ft_arg_error(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Number of argument incorrect.\nMust be ");
		printf("./Philo-chan number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	while (++i < ac)
	{
		if (av[i] < 0 || !ft_strisint(av[i]))
		{
			printf("Arg %d is either negatif or not a valid int.\n", i);
			return (1);
		}
	}
	return (0);
}

void	init_data(t_data *data, char **av)
{
	int		i;
	
	data->n_philos = ft_atoi(av[0]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_init(data->forks + i, NULL);
		pthread_mutex_init(&data->philos[i].mutex_task, NULL);
		pthread_mutex_init(&data->philos[i].mutex_eat, NULL);
		pthread_mutex_init(&data->philos[i].mutex_exit, NULL);
		pthread_mutex_init(&data->philos[i].mutex_angel, NULL);
	}
	pthread_mutex_init(&data->mic, NULL);
	data->philos_threads = malloc(sizeof(pthread_t) * data->n_philos);
	data->t_die = ft_atoi(av[1]);
	data->t_sleep = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_destroy(data->forks + i);
		pthread_mutex_destroy(&data->philos[i].mutex_task);
		pthread_mutex_destroy(&data->philos[i].mutex_eat);
		pthread_mutex_destroy(&data->philos[i].mutex_angel);
		pthread_mutex_destroy(&data->philos[i].mutex_exit);
	}
	pthread_mutex_unlock(&data->mic);
	pthread_mutex_destroy(&data->mic);
	free(data->philos);
	free(data->forks);
	free(data->philos_threads);
	free(data);
}

void	set_forks(t_data *data, int i)
{
	if (data->philos[i].id % 2)
	{
		data->philos[i].l_fork = data->forks + i;
		if (i < data->n_philos - 1)
			data->philos[i].r_fork = data->forks + i + 1;
		else
			data->philos[i].r_fork = data->forks;
	}
	else
	{
		data->philos[i].r_fork = data->forks + i;
		if (i < data->n_philos - 1)
			data->philos[i].l_fork = data->forks + i + 1;
		else
			data->philos[i].l_fork = data->forks;
	}
}

void	start_simulation(t_data *data)
{
	int		i;
	long	starting_time;

	starting_time = ft_time(0);
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].task = THINK;
		data->philos[i].t_die = data->t_die;
		data->philos[i].t_sleep = data->t_sleep;
		data->philos[i].t_eat = data->t_eat;
		data->philos[i].n_meals = 0;
		data->philos[i].max_meals = data->max_meals;
		data->philos[i].exited = 0;
		data->philos[i].mic = &data->mic;
		set_forks(data, i);
		data->philos[i].sim_start = starting_time;
	}
	i = -1;
	while (++i < data->n_philos)
	{
		pthread_create(data->philos_threads + i, NULL, philo_chan, data->philos + i);
		pthread_detach(data->philos_threads[i]);
	}
}

void	philocide(t_data *data)
{
	int		i;
	int		sum;

	i = -1;
	while (++i < data->n_philos)
		set_task(&data->philos[i].task, &data->philos[i].mutex_task, DEAD);
	sum = 0;
	while (sum != data->n_philos * 2)
	{
		i = -1;
		sum = 0;
		while (++i < data->n_philos)
		{
			sum += get_long(&data->philos[i].exited, &data->philos[i].mutex_exit);
			sum += get_long(&data->philos[i].angel, &data->philos[i].mutex_angel);
		}
	}
}

void	death_loop(t_data *data)
{
	int		i;
	int		break_point;
	int		meal;

	break_point = 1;
	while (break_point)
	{
		meal = 0;
		i = -1;
		while (++i < data->n_philos)
		{
			if (get_task(&data->philos[i].task, &data->philos[i].mutex_task) == DEAD)
			{
				break_point = 0;
				break ;
			}
			if (get_long(&data->philos[i].n_meals, &data->philos[i].mutex_eat) >= data->max_meals)
				meal++;
		}
		if (meal == data->n_philos)
			break ;
	}
	pthread_mutex_lock(&data->mic);
	if (meal != data->n_philos)
		printf("%ld\t%d died\n", ft_time(data->philos[i].t_start), i + 1);
	philocide(data);
}

int	main(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (ft_arg_error(ac, av))
		return (1);
	init_data(data, av + 1);
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	else
		data->max_meals = 2147483647;
	start_simulation(data);
	death_loop(data);
	free_data(data);
	return (0);
}