/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:04:56 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/13 15:25:14 by krain            ###   ########.fr       */
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
void	ft_usleep(long us);

#endif