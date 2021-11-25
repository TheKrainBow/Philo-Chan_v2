/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:19:33 by krain             #+#    #+#             */
/*   Updated: 2021/11/13 17:27:39 by krain            ###   ########.fr       */
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
		if (av[i] < 0 || !ft_strisint(av[i]))
		{
			printf("Arg %d is either negatif or not a valid int.\n", i);
			return (1);
		}
	}
	return (0);
}

void	philocide(t_data *d)
{
	int		i;
	int		sum;

	i = -1;
	while (++i < d->n_philos)
		set_task(&d->p[i].task, &d->p[i].mutex_task, DEAD);
	sum = 0;
	while (sum != d->n_philos * 2)
	{
		i = -1;
		sum = 0;
		while (++i < d->n_philos)
		{
			sum += get_long(&d->p[i].exited, &d->p[i].mutex_exit);
			sum += get_long(&d->p[i].angel, &d->p[i].mutex_angel);
			usleep(100);
		}
	}
	printf("All died!\n");
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
	pthread_mutex_lock(&d->mic);
	if (meal != d->n_philos)
		printf("%ld\t%d died\n", ft_time(d->p[i].t_start), i + 1);
	philocide(d);
}

void	one_philo(t_data *d)
{
	printf("0\t1 has taken a fork\n");
	usleep(d->t_die * 1000);
	printf("%ld\t1 died\n", d->t_die);
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
