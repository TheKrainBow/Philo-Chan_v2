/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:42:27 by magostin          #+#    #+#             */
/*   Updated: 2021/11/25 12:42:30 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include "color.h"
# include "struct.h"

int		ft_atoi(const char *str);
long	ft_time(long base_time);
int		ft_strisint(char *str);
t_task	get_task(t_task *val, pthread_mutex_t *mut);
long	get_long(long *val, pthread_mutex_t *mut);
void	set_task(t_task *val, pthread_mutex_t *mut, t_task new_val);
void	set_long(long *val, pthread_mutex_t *mut, long new_val);
void	*philo_chan(void *p);
void	init_data(t_data *d, char **av);
void	free_data(t_data *d);
void	start_simulation(t_data *d);
void	ft_usleep(long us, t_philo *philo);
void	*philo_angel(void *p);
int		ft_strlen(char *str);

#endif
