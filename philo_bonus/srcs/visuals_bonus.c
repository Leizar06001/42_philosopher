/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:52:25 by rloussig          #+#    #+#             */
/*   Updated: 2023/05/25 14:14:59 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	gotoxy(int x, int y)
{
	printf("\033[%d;%dH", (y), (x));
}

void	prt_titles(t_table *dt)
{
	int	i;

	gotoxy(1, 1);
	printf("Nb philo");
	gotoxy(21, 1);
	printf("Nb sitting");
	gotoxy(41, 1);
	printf("Dead ?");
	i = -1;
	while (++i * 20 < dt->nb_philo)
	{
		gotoxy(1, 3 + i * 8);
		printf("Philo");
		gotoxy(1, 4 + i * 8);
		printf("Alive");
		gotoxy(1, 5 + i * 8);
		printf("Sits");
		gotoxy(1, 6 + i * 8);
		printf("Meals");
		gotoxy(1, 7 + i * 8);
		printf("Nbfork");
	}
}

void	prt_graph(t_table *dt)
{
	int	i;

	gotoxy(11, 1);
	printf("%03d", dt->nb_philo);
	gotoxy(33, 1);
	printf("%03d", dt->nb_sitting);
	gotoxy(48, 1);
	printf("%03d", dt->stoop);
	i = -1;
	while (++i < dt->nb_philo)
	{
		gotoxy(10 + i % 20 * 4, 3 + i / 20 * 8);
		printf("|%d", i + 1);
		gotoxy(10 + i % 20 * 4, 4 + i / 20 * 8);
		printf("|%c", 64 + 56 * dt->ph[i]->alive);
		gotoxy(10 + i % 20 * 4, 5 + i / 20 * 8);
		printf("|%c", 32 + 88 * dt->ph[i]->sitting);
		gotoxy(10 + i % 20 * 4, 6 + i / 20 * 8);
		printf("|%d", dt->ph[i]->nb_meals);
		gotoxy(10 + i % 20 * 4, 7 + i / 20 * 8);
		printf("|%d", dt->ph[i]->nb_forks);
	}
}

void	init_visuals(t_table *dt)
{
	printf("\e[?25l");
	printf("\033[H\033[J");
	prt_titles(dt);
}
