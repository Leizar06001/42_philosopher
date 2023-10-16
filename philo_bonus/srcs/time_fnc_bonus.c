/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_fnc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:07:48 by rloussig          #+#    #+#             */
/*   Updated: 2023/05/25 14:12:00 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long long	get_usec(int msec)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (msec)
		return ((tv.tv_usec + tv.tv_sec * 1000000) / 1000);
	else
		return (tv.tv_usec + tv.tv_sec * 1000000);
}

long long	get_elapsed(t_table *dt)
{
	return (get_usec(1) - dt->start_t);
}
