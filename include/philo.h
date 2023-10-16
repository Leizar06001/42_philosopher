/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:51:31 by rloussig          #+#    #+#             */
/*   Updated: 2023/06/01 11:41:59 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	t_table			*dt;
	int				id;
	long long		t_left;
	pthread_mutex_t	*mleft_f;
	pthread_mutex_t	*mright_f;
	int				left_f;
	int				right_f;
	long long		start_life;
	pthread_mutex_t	mstart_life;
	long long		start_eat;
	long long		start_sleep;
	int				sitting;
	int				alive;
	int				first_round;
	int				nb_meals;
	int				enough_food;
	int				stoop;
	pthread_mutex_t	mstoop;
}				t_philo;

typedef struct s_table
{
	t_philo			ph[255][1];
	pthread_mutex_t	mforks[255];
	int				run_thread[255];
	int				nb_philo;
	int				nb_sitting;
	pthread_mutex_t	msitting;
	long long		life_t;
	long long		eat_t;
	long long		eat_n;
	long long		sleep_t;
	pthread_mutex_t	prt;
	long long		start_t;
	int				stoop;
	pthread_mutex_t	mstoop;
	int				nb_meals;
	int				visuals;
}				t_table;

long		fatoi(const char *str);

long long	get_usec(int msec);
long long	get_elapsed(t_table *dt);

int			init_struct(t_table *dt, int nb_philos);
int			fill_table(t_table *dt, int life_t, int eat_t, int sleep_t);

void		detroy_mutexs_and_threads(t_table *dt, pthread_t *th);
void		create_threads(t_table *dt, pthread_t *th);

int			philo_think(t_philo *ph);
int			philo_wait_right_fork(t_philo *ph);
int			philo_eats(t_philo *ph);
int			philo_unlock_forks(t_philo *ph);
int			philo_goto_sleep(t_philo *ph);

int			check_nb_meals(t_philo *ph);
int			philo_end_life(t_philo *ph);
int			check_stoop(t_philo *ph);
void		mod_stoop(t_table *dt, int val);

long long	check_lifetime(t_philo *ph);
void		reset_lifetime(t_philo *ph);
int			get_nb_sitting(t_table *dt);

void		prt_action(t_table *dt, long long time, int action, int ph);
void		*philo_life(void *arg);
void		check_death(t_table *dt);

void		prt_graph(t_table *dt);
void		prt_titles(t_table *dt);
void		init_visuals(t_table *dt);

#endif
