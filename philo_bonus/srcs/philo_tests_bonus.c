/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tests_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:02:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:25:00 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	check_nb_meals(t_philo *ph)
{
	if (ph->dt->nb_meals > 0)
	{
		if (ph->nb_meals >= ph->dt->nb_meals)
		{
			ph->enough_food = 1;
			return (1);
		}
	}
	return (0);
}

int	philo_end_life(t_philo *ph)
{
	ph->sitting = 0;
	sem_wait(&(ph->dt->sem_nb_sitting));
	ph->dt->nb_sitting--;
	sem_post(&(ph->dt->sem_nb_sitting));
	if (!ph->dt->stoop)
		prt_action(ph->dt, get_elapsed(ph->dt), 8, ph->id);
	return (0);
}

int	check_stoop(t_philo *ph)
{
	int	ret;

	sem_wait(&(ph->sem_stoop));
	ret = ph->stoop;
	sem_post(&(ph->sem_stoop));
	return (ret);
}

void	mod_stoop(t_table *dt, int val)
{
	int	i;

	sem_wait(&(dt->sem_stoop));
	dt->stoop = val;
	sem_post(&(dt->sem_stoop));
	i = -1;
	while (++i < dt->nb_philo)
	{
		sem_wait(&(dt->ph[i]->sem_stoop));
		dt->ph[i]->stoop = val;
		sem_post(&(dt->ph[i]->sem_stoop));
	}
}
