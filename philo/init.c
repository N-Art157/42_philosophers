/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:52:09 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/23 17:06:07 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	parse_arguments(int argc, char **argv)
{
	t_rules			rules;
	int				i;

	if (argc != 5 && argc != 6)
		error_handler(INVALID_ARGUMENTS, NULL, NULL);
	i = argc;
	while (i-- > 1)
	{
		if (!str_is_int(argv[i]) || ft_atoi(argv[i]) <= 0)
			error_handler(INVALID_ARGUMENTS, NULL, NULL);
	}
	rules.num_of_philos = ft_atoi(argv[1]);
	if (rules.num_of_philos > MAX_PHILOS)
		error_handler(TOO_MANY_PHILOS, NULL, NULL);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules.times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		rules.times_each_philo_must_eat = -1;
	return (rules);
}

static void	init_forks(t_game *game)
{
	int		i;

	game->forks = (t_fork *)malloc(sizeof(t_fork) * game->rules.num_of_philos);
	if (game->forks == NULL)
		error_handler(FAIL_TO_INIT, NULL, game);
	i = 0;
	game->n_forks_inited = 0;
	while (i < game->rules.num_of_philos)
	{
		if (pthread_mutex_init(&game->forks[i].mutex, NULL))
			error_handler(FAIL_TO_INIT, NULL, game);
		game->n_forks_inited++;
		if (i % 2 == 0)
			game->forks[i].status = F_USED_R;
		else
			game->forks[i].status = F_USED_L;
		i++;
	}
}

static void	init_philo(t_game *game, int id, t_fork *l, t_fork *r)
{
	t_philo	*philo;

	philo = &game->philos[id - 1];
	philo->game = game;
	philo->id = id;
	philo->times_ate = 0;
	philo->fork_r = r;
	philo->fork_l = l;
	philo->status = P_FREE;
	if (pthread_mutex_init(&philo->mutex, NULL))
		error_handler(FAIL_TO_INIT, NULL, game);
	game->n_philo_locks_inited++;
}

static void	init_philos(t_game *game)
{
	int		i;

	game->philos = (t_philo *)
		malloc(sizeof(t_philo) * game->rules.num_of_philos);
	if (game->philos == NULL)
		error_handler(FAIL_TO_INIT, NULL, game);
	game->n_philos_inited = 0;
	game->n_philo_locks_inited = 0;
	init_philo
		(game, 1, &game->forks[game->rules.num_of_philos - 1], &game->forks[0]);
	i = 1;
	while (i < game->rules.num_of_philos)
	{
		init_philo(game, i + 1, &game->forks[i - 1], &game->forks[i]);
		i++;
	}
}

void	init_game(t_game *game)
{
	game->n_forks_inited = G_UNINIT;
	game->n_philos_inited = G_UNINIT;
	game->status_lock_inited = G_UNINIT;
	game->time_lock_inited = G_UNINIT;
	game->gameover_checker_inited = G_UNINIT;
	game->n_forks_inited = G_UNINIT;
	game->status = G_INIT;
	init_forks(game);
	init_philos(game);
	if (pthread_mutex_init(&game->status_lock, NULL))
		error_handler(FAIL_TO_INIT, NULL, game);
	game->status_lock_inited = 1;
	if (pthread_mutex_init(&game->time_lock, NULL))
		error_handler(FAIL_TO_INIT, NULL, game);
	game->time_lock_inited = 1;
}
