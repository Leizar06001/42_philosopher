/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:09:04 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:42:32 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// **************************************************
// USE NEGATIVE NUMBER OF PHILOSOPHER TO GET A VISUAL
// REPRESENTATION OF THE TABLE
// **************************************************

#include "../include/philo.h"

void	*philo_life(void *arg)
{
	t_philo			*ph;

	ph = arg;
	reset_lifetime(ph);
	while (!check_stoop(ph))
	{
		philo_think(ph);
		if (check_stoop(ph))
			break ;
		philo_wait_right_fork(ph);
		if (check_stoop(ph))
			break ;
		philo_eats(ph);
		reset_lifetime(ph);
		if (check_stoop(ph) || check_nb_meals(ph))
			break ;
		philo_goto_sleep(ph);
	}
	philo_unlock_forks(ph);
	philo_end_life(ph);
	return (NULL);
}

void	check_death(t_table *dt)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < dt->nb_philo)
		{
			if (dt->visuals)
				prt_graph(dt);
			if (dt->run_thread[i])
			{
				if (get_usec(0) - check_lifetime(dt->ph[i]) > dt->life_t * 1000
					&& dt->ph[i]->enough_food == 0)
				{
					prt_action(dt, get_elapsed(dt), 5, i + 1);
					dt->ph[i]->alive = 0;
					mod_stoop(dt, 1);
					return ;
				}
				usleep(1000);
			}
			if (get_nb_sitting(dt) == 0)
				return ;
		}
	}
}

int	check_visuals(t_table *dt, char **av)
{
	if (fatoi(av[1]) < 0)
	{
		dt->visuals = 1;
		if (init_struct(dt, -1 * fatoi(av[1])))
			return (1);
	}
	else
	{
		dt->visuals = 0;
		if (init_struct(dt, fatoi(av[1])))
			return (1);
	}
	return (0);
}

int	main(int argc, char **av)
{
	pthread_t	th[255];
	t_table		dt;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments !\n");
		return (0);
	}
	if (check_visuals(&dt, av))
		return (1);
	if (fill_table(&dt, fatoi(av[2]), fatoi(av[3]), fatoi(av[4])))
		return (1);
	if (argc == 6)
		dt.nb_meals = fatoi(av[5]);
	if (dt.visuals)
		init_visuals(&dt);
	create_threads(&dt, th);
	usleep(dt.life_t * 500);
	check_death(&dt);
	detroy_mutexs_and_threads(&dt, th);
	printf("\e[?25h");
	return (0);
}

//valgrind --tool=helgrind --tool=drd -s
// **************************************************
// USE NEGATIVE NUMBER OF PHILOSOPHER TO GET A VISUAL
// REPRESENTATION OF THE TABLE
// **************************************************
