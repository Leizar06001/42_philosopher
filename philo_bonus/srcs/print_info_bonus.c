/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:26:56 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:39:54 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	sem_print(t_table *dt, char *str, long long time, int ph)
{
	sem_wait(&(dt->sem_print));
	printf("%010lld % 4d %s", time, ph, str);
	sem_post(&(dt->sem_print));
}

void	prt_action(t_table *dt, long long time, int action, int ph)
{
	if (!dt->visuals)
	{
		sem_wait(&(dt->sem_stoop));
		if (action == 0 && dt->stoop == 0)
			sem_print(dt, "is thinking\n", time, ph);
		else if (action == 1 && dt->stoop == 0)
			sem_print(dt, "has taken left fork\n", time, ph);
		else if (action == 2 && dt->stoop == 0)
			sem_print(dt, "is eating\n", time, ph);
		else if (action == 3 && dt->stoop == 0)
			sem_print(dt, "is sleeping\n", time, ph);
		else if (action == 4)
			sem_print(dt, "sits at the table\n", time, ph);
		else if (action == 5)
			sem_print(dt, "DIED OF HUNGER !!\n", time, ph);
		else if (action == 6)
			sem_print(dt, "left the table horrified !\n", time, ph);
		else if (action == 7)
			sem_print(dt, "lies dead on its chair...\n", time, ph);
		else if (action == 8)
			sem_print(dt, "has got enough and left the table\n", time, ph);
		else if (action == 9)
			sem_print(dt, "thread closed\n", time, ph);
		sem_post(&(dt->sem_stoop));
	}
}
