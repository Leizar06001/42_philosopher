/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:08:52 by rloussig          #+#    #+#             */
/*   Updated: 2023/05/24 14:01:07 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	if (pthread_mutex_init(&(dt->prt), NULL) == -1)
		return (1);
	if (pthread_mutex_init(&(dt->msitting), NULL) == -1)
		return (1);
	if (pthread_mutex_init(&(dt->mstoop), NULL) == -1)
		return (1);
	return (0);
}

void	choose_fork(t_table *dt)
{
	int	i;

	i = 0;
	dt->ph[i]->mleft_f = &(dt->mforks[0]);
	dt->ph[i]->mright_f = &(dt->mforks[1]);
	while (++i < dt->nb_philo)
	{
		if (i % 2)
		{
			dt->ph[i]->mleft_f = &(dt->mforks[i]);
			if (i < dt->nb_philo - 1)
				dt->ph[i]->mright_f = &(dt->mforks[i + 1]);
			else
				dt->ph[i]->mright_f = &(dt->mforks[0]);
		}
		else
		{
			if (i < dt->nb_philo - 1)
				dt->ph[i]->mleft_f = &(dt->mforks[i + 1]);
			else
				dt->ph[i]->mleft_f = &(dt->mforks[0]);
			dt->ph[i]->mright_f = &(dt->mforks[i]);
		}
	}
}

int	mutex_forks(t_table *dt)
{
	int	i;

	i = -1;
	while (++i < dt->nb_philo + 1)
	{
		if (pthread_mutex_init(&(dt->mforks[i]), NULL) == -1)
			return (1);
	}
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
		dt->ph[i]->left_f = 0;
		dt->ph[i]->alive = 1;
		dt->ph[i]->first_round = 1;
		dt->ph[i]->nb_meals = 0;
		dt->ph[i]->enough_food = 0;
		dt->ph[i]->stoop = 0;
		prt_action(dt, get_elapsed(dt), 4, i + 1);
		if (pthread_mutex_init(&(dt->ph[i]->mstoop), NULL) == -1)
			return (1);
	}
	if (mutex_forks(dt))
		return (1);
	choose_fork(dt);
	return (0);
}
