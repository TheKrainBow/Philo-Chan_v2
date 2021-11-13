/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:33:29 by krain             #+#    #+#             */
/*   Updated: 2021/11/13 17:25:14 by krain            ###   ########.fr       */
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
	*val = new_val;
	pthread_mutex_unlock(mut);
}

void	set_long(long *val, pthread_mutex_t *mut, long new_val)
{
	pthread_mutex_lock(mut);
	*val = new_val;
	pthread_mutex_unlock(mut);
}
