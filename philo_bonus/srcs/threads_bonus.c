/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:06:51 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:31:21 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	detroy_sems_and_threads(t_table *dt, pthread_t *th)
{
	int	i;
	int	nb_left;

	if (dt->visuals)
		prt_graph(dt);
	i = -1;
	nb_left = 0;
	while (++i < dt->nb_philo)
	{
		pthread_join(th[i], NULL);
		nb_left++;
		if (dt->stoop && dt->ph[i]->enough_food == 0)
		{
			if (dt->ph[i]->alive == 1)
				prt_action(dt, get_elapsed(dt), 6, i + 1);
			else
				prt_action(dt, get_elapsed(dt), 7, i + 1);
		}
	}
	sem_destroy(&(dt->sem_stoop));
	sem_destroy(&(dt->sem_print));
	sem_destroy(&(dt->sem_forks));
	sem_destroy(&(dt->sem_nb_sitting));
}

void	create_threads(t_table *dt, pthread_t *th)
{
	int	i;

	i = -1;
	while (++i < dt->nb_philo)
	{
		pthread_create(&th[i], NULL, philo_life, dt->ph[i]);
		sem_wait(&(dt->sem_nb_sitting));
		dt->nb_sitting++;
		sem_post(&(dt->sem_nb_sitting));
	}
	i = -1;
	while (++i < dt->nb_philo)
		sem_wait(&(dt->sem_nb_threads_started));
}

void	wait_all_threads(t_philo *ph)
{
	int	i;

	sem_post(&(ph->dt->sem_nb_threads_started));
	i = 0;
	while (i < ph->nb_philo)
	{
		sem_wait(&(ph->dt->sem_nb_sitting));
		i = ph->dt->nb_sitting;
		sem_post(&(ph->dt->sem_nb_sitting));
		usleep(100);
	}
}
