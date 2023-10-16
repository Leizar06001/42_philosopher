/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:02:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/05/24 12:06:35 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	pthread_mutex_lock(&(ph->dt->msitting));
	ph->dt->nb_sitting--;
	pthread_mutex_unlock(&(ph->dt->msitting));
	if (!ph->dt->stoop)
		prt_action(ph->dt, get_elapsed(ph->dt), 8, ph->id);
	return (0);
}

int	check_stoop(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(&(ph->mstoop));
	ret = ph->stoop;
	pthread_mutex_unlock(&(ph->mstoop));
	return (ret);
}

void	mod_stoop(t_table *dt, int val)
{
	int	i;

	pthread_mutex_lock(&(dt->mstoop));
	dt->stoop = val;
	pthread_mutex_unlock(&(dt->mstoop));
	i = -1;
	while (++i < dt->nb_philo)
	{
		pthread_mutex_lock(&(dt->ph[i]->mstoop));
		dt->ph[i]->stoop = val;
		pthread_mutex_unlock(&(dt->ph[i]->mstoop));
	}
}
