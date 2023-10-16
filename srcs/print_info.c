/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:26:56 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:40:20 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	mutex_print(t_table *dt, char *str, long long time, int ph)
{
	pthread_mutex_lock(&(dt->prt));
	printf("%010lld % 4d %s", time, ph, str);
	pthread_mutex_unlock(&(dt->prt));
}

void	prt_action(t_table *dt, long long time, int action, int ph)
{
	if (!dt->visuals)
	{
		pthread_mutex_lock(&(dt->mstoop));
		if (action == 0 && dt->stoop == 0)
			mutex_print(dt, "is thinking\n", time, ph);
		else if (action == 1 && dt->stoop == 0)
			mutex_print(dt, "has taken left fork\n", time, ph);
		else if (action == 2 && dt->stoop == 0)
			mutex_print(dt, "is eating\n", time, ph);
		else if (action == 3 && dt->stoop == 0)
			mutex_print(dt, "is sleeping\n", time, ph);
		else if (action == 4)
			mutex_print(dt, "sits at the table\n", time, ph);
		else if (action == 5)
			mutex_print(dt, "DIED OF HUNGER !!\n", time, ph);
		else if (action == 6)
			mutex_print(dt, "left the table horrified !\n", time, ph);
		else if (action == 7)
			mutex_print(dt, "lies dead on its chair...\n", time, ph);
		else if (action == 8)
			mutex_print(dt, "has got enough and left the table\n", time, ph);
		else if (action == 9)
			mutex_print(dt, "thread closed\n", time, ph);
		pthread_mutex_unlock(&(dt->mstoop));
	}
}
