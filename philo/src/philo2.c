/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 21:23:33 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/01 21:05:45 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //# usleep
#include "philo.h"
#include "str.h"

enum e_philo_state	state_philo_one(t_philo *philo)
{
	#ifdef DEBUG_FLAG
		pthread_mutex_lock(&philo->share->mutex_end);
		printf("DEBUG: philo %d enter one\n", philo->i + 1);
		pthread_mutex_unlock(&philo->share->mutex_end);
	#endif
	while (1)
	{
		if (pthread_mutex_lock(&philo->share->mutex_end))
			return (printf("fail thread %d lock mutex_end one\n", philo->i + 1));
		#ifdef DEBUG_FLAG
			printf("DEBUG: thread %d lock mutex_end\n", philo->i + 1);
		#endif
		if (philo->share->flag_end)
		{
			if (pthread_mutex_unlock(&philo->share->mutex_end))
				return (printf("fail thread %d unlock mutex_end one\n", philo->i + 1));
			if (pthread_mutex_unlock(&philo->left_fork))
				return (printf("fail thread %d unlock left_fork\n", philo->i + 1));
			return (STATE_PHILO_DIE);
		}
		#ifdef DEBUG_FLAG
		printf("DEBUG: thread %d unlock mutex_end\n", philo->i + 1);
		#endif
		if (pthread_mutex_unlock(&philo->share->mutex_end))
			return (printf("fail thread %d unlock mutex_end one\n", philo->i + 1));
		usleep(2000);
	}
}

enum e_philo_state	state_philo_think(t_philo *philo)
{
	if (philo->share->flag_end)
	{
		#ifdef DEBUG_FLAG
			pthread_mutex_lock(&philo->share->mutex_end);
			printf("DEBUG: philo %d finish in think\n", philo->i + 1);
			pthread_mutex_unlock(&philo->share->mutex_end);
		#endif
		return (STATE_PHILO_DIE);
	}
	if (print_status(philo, STATE_PHILO_THINK))
		return (STATE_PHILO_ERROR);
	if (philo->i % 2 && 0 == philo->once++)
		return (STATE_PHILO_SLEEP);
	return (STATE_PHILO_FORK);
}

enum e_philo_state	state_philo_sleep(t_philo *philo)
{
	if (philo->share->flag_end)
	{
		#ifdef DEBUG_FLAG
			pthread_mutex_lock(&philo->share->mutex_end);
			printf("DEBUG: philo %d finish in sleep\n", philo->i + 1);
			pthread_mutex_unlock(&philo->share->mutex_end);
		#endif
		return (STATE_PHILO_DIE);
	}
	if (print_status(philo, STATE_PHILO_SLEEP))
		return (STATE_PHILO_ERROR);
	usleep(get_time_us(philo->share->time[PHILO_TIME_SLEEP]));
	return (STATE_PHILO_THINK);
}
