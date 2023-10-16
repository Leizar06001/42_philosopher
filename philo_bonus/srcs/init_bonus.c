/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:08:52 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:30:00 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	init_semaphores(t_table *dt)
{
	if (sem_init(&(dt->sem_stoop), 0, 1) == -1)
		return (1);
	if (sem_init(&(dt->sem_print), 0, 1) == -1)
		return (1);
	if (sem_init(&(dt->sem_forks), 0, dt->nb_philo) == -1)
		return (1);
	if (sem_init(&(dt->sem_nb_sitting), 0, dt->nb_philo) == -1)
		return (1);
	if (sem_init(&(dt->sem_nb_threads_started), 0, 0) == -1)
		return (1);
	return (0);
}

int	init_struct(t_table *dt, int nb_philos)
{
	int	i;

	i = -1;
	while (++i < nb_philos)
	{
		dt->ph[i]->dt = dt;
		dt->ph[i]->id = i + 1;
	}
	i = -1;
	while (++i < 255)
		dt->run_thread[i] = 0;
	dt->nb_sitting = 0;
	dt->nb_philo = nb_philos;
	dt->start_t = get_usec(1);
	dt->stoop = 0;
	dt->nb_meals = 0;
	if (init_semaphores(dt))
		return (1);
	return (0);
}

int	fill_table(t_table *dt, int life_t, int eat_t, int sleep_t)
{
	int	i;

	dt->life_t = life_t;
	dt->eat_t = eat_t;
	dt->sleep_t = sleep_t;
	i = -1;
	while (++i < dt->nb_philo)
	{
		dt->run_thread[i] = 1;
		dt->ph[i]->sitting = 1;
		dt->ph[i]->alive = 1;
		dt->ph[i]->first_round = 1;
		dt->ph[i]->nb_meals = 0;
		dt->ph[i]->enough_food = 0;
		dt->ph[i]->stoop = 0;
		dt->ph[i]->nb_forks = 0;
		dt->ph[i]->nb_philo = dt->nb_philo;
		prt_action(dt, get_elapsed(dt), 4, i + 1);
		if (sem_init(&(dt->ph[i]->sem_stoop), 0, 1) == -1)
			return (1);
		if (sem_init(&(dt->ph[i]->sem_start_life), 0, 1) == -1)
			return (1);
	}
	return (0);
}
