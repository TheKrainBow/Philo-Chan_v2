/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:43:00 by magostin          #+#    #+#             */
/*   Updated: 2021/11/25 12:43:02 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_task	get_task(t_task *val, pthread_mutex_t *mut)
{
	t_task	ret;

	pthread_mutex_lock(mut);
	ret = *val;
	pthread_mutex_unlock(mut);
	return (ret);
}

long	get_long(long *val, pthread_mutex_t *mut)
{
	long	ret;

	pthread_mutex_lock(mut);
	ret = *val;
	pthread_mutex_unlock(mut);
	return (ret);
}

void	set_task(t_task *val, pthread_mutex_t *mut, t_task new_val)
{
	pthread_mutex_lock(mut);
	if (*val != DEAD || *val == EAT)
		*val = new_val;
	pthread_mutex_unlock(mut);
}

void	set_long(long *val, pthread_mutex_t *mut, long new_val)
{
	pthread_mutex_lock(mut);
	*val = new_val;
	pthread_mutex_unlock(mut);
}
