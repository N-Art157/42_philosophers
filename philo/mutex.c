/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:53:34 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/23 17:06:15 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_mutex_value(int *p, pthread_mutex_t *lock)
{
	int	value;

	pthread_mutex_lock(lock);
	value = *p;
	pthread_mutex_unlock(lock);
	return (value);
}

long	get_mutex_long(long *p, pthread_mutex_t *lock)
{
	long	value;

	pthread_mutex_lock(lock);
	value = *p;
	pthread_mutex_unlock(lock);
	return (value);
}

void	set_mutex_value(int *p, int value, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*p = value;
	pthread_mutex_unlock(lock);
}

void	set_mutex_long(long *p, long value, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*p = value;
	pthread_mutex_unlock(lock);
}
