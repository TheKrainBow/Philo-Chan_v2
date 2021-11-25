/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:42:48 by magostin          #+#    #+#             */
/*   Updated: 2021/11/25 12:42:50 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
		if (ft_atoi(av[i]) <= 0 || !ft_strisint(av[i]) || ft_strlen(av[i]) > 10)
		{
			printf("Arg %d is either negatif or not a valid int.\n", i);
			return (1);
		}
	}
	return (0);
}

void	philocide(t_data *d, int meal, int i)
{
	long	sum;

	pthread_mutex_lock(&d->mic);
	if (meal != d->n_philos)
		printf("%5ld  %d died\n", ft_time(d->p[i].t_start), i + 1);
	else
		printf("-- Everybody ate %ld times --\n", d->max_meals);
	i = -1;
	while (++i < d->n_philos)
		set_task(&d->p[i].task, &d->p[i].mutex_task, DEAD);
	pthread_mutex_unlock(&d->mic);
	sum = 1;
	while (sum)
	{
		i = -1;
		sum = 0;
		while (++i < d->n_philos)
		{
			sum += get_long(&d->p[i].exited, &d->p[i].mutex_exit);
			sum += get_long(&d->p[i].angel, &d->p[i].mutex_angel);
		}
	}
}

void	death_loop(t_data *d)
{
	int		i;
	int		break_point;
	int		meal;

	meal = 0;
	break_point = 1;
	while (break_point && meal != d->n_philos)
	{
		meal = 0;
		i = -1;
		while (++i < d->n_philos)
		{
			if (get_task(&d->p[i].task, &d->p[i].mutex_task) == DEAD)
			{
				break_point = 0;
				break ;
			}
			if (get_long(&d->p[i].n_meals, &d->p[i].mutex_eat) >= d->max_meals)
				meal++;
		}
	}
	philocide(d, meal, i);
}

void	one_philo(t_data *d)
{
	printf("%5d  %d has taken a fork\n", 0, 1);
	usleep(d->t_die * 1000);
	printf("%5ld  %d died\n", d->t_die, 1);
}

int	main(int ac, char **av)
{
	t_data		*d;

	d = malloc(sizeof(t_data));
	if (ft_arg_error(ac, av))
		return (1);
	init_data(d, av + 1);
	if (ac == 6)
		d->max_meals = ft_atoi(av[5]);
	else
		d->max_meals = 2147483647;
	if (d->n_philos == 1)
		one_philo(d);
	else
	{
		start_simulation(d);
		death_loop(d);
	}
	free_data(d);
	return (0);
}
