/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:53:14 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/23 17:06:12 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_game			game;

	game.rules = parse_arguments(argc, argv);
	init_game(&game);
	create_philos(&game);
	create_gameover_checker(&game);
	set_mutex_value(&game.status, G_START, &game.status_lock);
	while (1)
		;
}
