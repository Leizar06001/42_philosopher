/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:06:51 by rloussig          #+#    #+#             */
/*   Updated: 2023/05/24 10:28:39 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	detroy_mutexs_and_threads(t_table *dt, pthread_t *th)
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
}

void	create_threads(t_table *dt, pthread_t *th)
{
	int	i;

	i = -1;
	while (++i < dt->nb_philo)
	{
		pthread_create(&th[i], NULL, philo_life, dt->ph[i]);
		dt->nb_sitting++;
	}
}
