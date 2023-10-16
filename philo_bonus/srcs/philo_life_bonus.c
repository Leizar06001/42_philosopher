/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:40:18 by rloussig          #+#    #+#             */
/*   Updated: 2023/05/25 14:21:53 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
	sem_wait(&(ph->dt->sem_forks));
	ph->nb_forks++;
	return (0);
}

int	philo_wait_right_fork(t_philo *ph)
{
	prt_action(ph->dt, get_elapsed(ph->dt), 1, ph->id);
	if (ph->dt->nb_philo < 2)
		usleep(ph->dt->life_t * 1000);
	else
	{
		sem_wait(&(ph->dt->sem_forks));
		ph->nb_forks++;
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
	while (ph->nb_forks)
	{
		sem_post(&(ph->dt->sem_forks));
		ph->nb_forks--;
	}
	return (0);
}

int	philo_goto_sleep(t_philo *ph)
{
	philo_unlock_forks(ph);
	prt_action(ph->dt, get_elapsed(ph->dt), 3, ph->id);
	usleep(ph->dt->sleep_t * 1000);
	return (0);
}
