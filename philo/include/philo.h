/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:31:26 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/01 18:07:38 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include "ft_time.h"
#include "debug.h" //#

typedef struct s_share
{
	bool			flag_end;
	pthread_mutex_t	mutex_end;
	struct timeval	start_time;
	struct timeval	time[3];
	int				must_eat;
}	t_share;

enum e_philo_state
{
	STATE_PHILO_ERROR = -1,
	STATE_PHILO_FORK,
	STATE_PHILO_EAT,
	STATE_PHILO_THINK,
	STATE_PHILO_SLEEP,
	STATE_PHILO_DIE,
	STATE_PHILO_ONE,
};

typedef struct s_philo
{
	t_share				*share;
	pthread_t			thread;
	int					i;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	struct timeval		last_meal;
	enum e_philo_state	state;
	int					eat_cnt;
	int					once;
}	t_philo;

enum e_philo_time
{
	PHILO_TIME_DIE,
	PHILO_TIME_EAT,
	PHILO_TIME_SLEEP,
};

typedef struct s_simul
{
	t_share	*share;
	t_philo	*philos;
	int		num;
}	t_simul;

/*
* philo.c
*/
enum e_philo_state	state_philo_fork(t_philo *philo);
enum e_philo_state	state_philo_eat(t_philo *philo);
enum e_philo_state	state_philo_think(t_philo *philo);
enum e_philo_state	state_philo_sleep(t_philo *philo);
enum e_philo_state	state_philo_one(t_philo *philo);
void				*philo_run(void *arg);

#endif
