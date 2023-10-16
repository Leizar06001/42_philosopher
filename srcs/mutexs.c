/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:42:12 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:42:23 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	check_lifetime(t_philo *ph)
{
	long long	ret;

	pthread_mutex_lock(&(ph->mstart_life));
	ret = ph->start_life;
	pthread_mutex_unlock(&(ph->mstart_life));
	return (ret);
}

void	reset_lifetime(t_philo *ph)
{
	pthread_mutex_lock(&(ph->mstart_life));
	ph->start_life = get_usec(0);
	pthread_mutex_unlock(&(ph->mstart_life));
}

int	get_nb_sitting(t_table *dt)
{
	int	i;

	pthread_mutex_lock(&(dt->msitting));
	i = dt->nb_sitting;
	pthread_mutex_unlock(&(dt->msitting));
	return (i);
}
