/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:54:47 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/23 17:06:21 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_milliseconds	now_e(t_philo *philo)
{
	struct timeval	time_current;
	t_milliseconds	timestamp;

	if (gettimeofday(&time_current, NULL) == -1)
		error_handler(RUNTIME_ERROR, &philo->thread, philo->game);
	timestamp = time_current.tv_sec * 1000 + time_current.tv_usec / 1000;
	return (timestamp);
}

static t_milliseconds	now(void)
{
	struct timeval	time_current;
	t_milliseconds	timestamp;

	if (gettimeofday(&time_current, NULL) == -1)
		return (-1);
	timestamp = time_current.tv_sec * 1000 + time_current.tv_usec / 1000;
	return (timestamp);
}

void	timestamp(t_philo *philo, char *str)
{
	t_milliseconds	timestamp;
	t_game			*game;

	game = philo->game;
	pthread_mutex_lock(&game->time_lock);
	timestamp = now();
	if (timestamp == -1)
	{
		pthread_mutex_unlock(&game->time_lock);
		error_handler(RUNTIME_ERROR, &philo->thread, game);
	}
	if (get_mutex_value(&game->status, &game->status_lock) == G_START)
		printf("%lu %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&game->time_lock);
}
