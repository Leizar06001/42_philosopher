/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:42:12 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:24:03 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long long	check_lifetime(t_philo *ph)
{
	long long	ret;

	sem_wait(&(ph->sem_start_life));
	ret = ph->start_life;
	sem_post(&(ph->sem_start_life));
	return (ret);
}

void	reset_lifetime(t_philo *ph)
{
	sem_wait(&(ph->sem_start_life));
	ph->start_life = get_usec(0);
	sem_post(&(ph->sem_start_life));
}

int	get_nb_sitting(t_table *dt)
{
	int	i;

	sem_wait(&(dt->sem_nb_sitting));
	i = dt->nb_sitting;
	sem_post(&(dt->sem_nb_sitting));
	return (i);
}
