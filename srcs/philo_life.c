/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:40:18 by rloussig          #+#    #+#             */
/*   Updated: 2023/05/24 14:22:22 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_think(t_philo *ph)
{
	prt_action(ph->dt, get_elapsed(ph->dt), 0, ph->id);
	if (ph->first_round && ph->id % 2)
	{
		usleep(ph->dt->life_t * 200);
		ph->first_round = 0;
	}
	usleep((ph->dt->life_t * 1000 - (get_usec(0)
				- check_lifetime(ph))) / 700);
	pthread_mutex_lock(ph->mleft_f);
	ph->left_f = 1;
	return (0);
}

int	philo_wait_right_fork(t_philo *ph)
{
	prt_action(ph->dt, get_elapsed(ph->dt), 1, ph->id);
	if (ph->dt->nb_philo < 2)
		usleep(ph->dt->life_t * 1000);
	else
	{
		pthread_mutex_lock(ph->mright_f);
		ph->right_f = 1;
	}
	return (0);
}

int	philo_eats(t_philo *ph)
{
	prt_action(ph->dt, get_elapsed(ph->dt), 2, ph->id);
	usleep(ph->dt->eat_t * 1000);
	ph->nb_meals++;
	return (0);
}

int	philo_unlock_forks(t_philo *ph)
{
	if (ph->left_f == 1)
		pthread_mutex_unlock(ph->mleft_f);
	if (ph->right_f == 1)
		pthread_mutex_unlock(ph->mright_f);
	ph->left_f = 0;
	ph->right_f = 0;
	return (0);
}

int	philo_goto_sleep(t_philo *ph)
{
	philo_unlock_forks(ph);
	prt_action(ph->dt, get_elapsed(ph->dt), 3, ph->id);
	usleep(ph->dt->sleep_t * 1000);
	return (0);
}
