/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:31:26 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/27 11:40:41 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

enum e_philo_state
{
	STATE_PHILO_EAT,
	STATE_PHILO_THINK,
	STATE_PHILO_SLEEP,
	STATE_PHILO_DIE,
};

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_meal;
}	t_philo;

enum e_philo_time
{
	PHILO_TIME_DIE,
	PHILO_TIME_EAT,
	PHILO_TIME_SLEEP,
};

typedef struct s_simul
{
	int				flag_end;
	struct timeval	time_start;
	int				num;
	suseconds_t		time[3];
	int				must_eat;
}	t_simul;

/*
* philo.c
*/
int	setting_table();

#endif
