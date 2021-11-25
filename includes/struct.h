/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:42:34 by magostin          #+#    #+#             */
/*   Updated: 2021/11/25 12:42:36 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_task {
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_task;

typedef struct s_philo
{
	int					id;
	t_task				task;
	pthread_mutex_t		mutex_task;
	long				t_die;
	long				t_sleep;
	long				t_eat;
	long				t_start;
	long				sim_start;
	long				t_last_eat;
	pthread_mutex_t		mutex_eat;
	long				n_meals;
	long				max_meals;
	long				exited;
	pthread_mutex_t		mutex_exit;
	long				angel;
	pthread_mutex_t		mutex_angel;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*mic;
}	t_philo;

typedef struct s_data
{
	t_philo				*p;
	pthread_t			*philos_threads;
	pthread_t			*angel_threads;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mic;
	long				t_die;
	long				t_sleep;
	long				t_eat;
	long				max_meals;
	int					n_philos;
}	t_data;

#endif