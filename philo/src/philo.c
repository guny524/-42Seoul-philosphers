/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:51:23 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/01 21:05:41 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //# usleep
#include <stdio.h>
#include "philo.h"
#include "str.h"

enum e_philo_state	state_philo_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->left_fork))
		return (printf("fail thread %d lock left_fork\n", philo->i + 1));
	#ifdef DEBUG_FLAG
		pthread_mutex_lock(&philo->share->mutex_end);
		printf("DEBUG: philo %d lock left\n", philo->i + 1);
		pthread_mutex_unlock(&philo->share->mutex_end);
	#endif
	if (philo->share->flag_end)
	{
		#ifdef DEBUG_FLAG
			pthread_mutex_lock(&philo->share->mutex_end);
			printf("DEBUG: philo %d finish with unlock left\n", philo->i + 1);
			pthread_mutex_unlock(&philo->share->mutex_end);
		#endif
		if (pthread_mutex_unlock(&philo->left_fork))
			return (printf("fail thread %d unlock left_fork\n", philo->i + 1));
		return (STATE_PHILO_DIE);
	}
	if (print_status(philo, STATE_PHILO_FORK))
		return (STATE_PHILO_ERROR);
	if (NULL == philo->right_fork)
		return (STATE_PHILO_ONE);
	return (STATE_PHILO_EAT);
}

enum e_philo_state	state_philo_eat(t_philo *philo)
{
	struct timeval	current_time;

	if (pthread_mutex_lock(philo->right_fork))
		return (printf("fail thread %d lock right_fork\n", philo->i + 1));
	#ifdef DEBUG_FLAG
		pthread_mutex_lock(&philo->share->mutex_end);
		printf("DEBUG: philo %d lock right\n", philo->i + 1);
		pthread_mutex_unlock(&philo->share->mutex_end);
	#endif
	if (philo->share->flag_end)
	{
		#ifdef DEBUG_FLAG
			pthread_mutex_lock(&philo->share->mutex_end);
			printf("DEBUG: philo %d finish with unlock left right\n", philo->i + 1);
			pthread_mutex_unlock(&philo->share->mutex_end);
		#endif
		if (pthread_mutex_unlock(philo->right_fork))
			return (printf("fail thread %d unlock right_fork\n", philo->i + 1));
		if (pthread_mutex_unlock(&philo->left_fork))
			return (printf("fail thread %d unlock left_fork\n", philo->i + 1));
		return (STATE_PHILO_DIE);
	}
	if (print_status(philo, STATE_PHILO_EAT))
		return (STATE_PHILO_ERROR);
	if (gettimeofday(&current_time, NULL))
		return (printf("fail thread %d update current_time\n", philo->i + 1));
	while (compare_time(sub_time(current_time, philo->last_meal),
		philo->share->time[PHILO_TIME_EAT]) < 0)
	{
		#ifdef DEBUG_FLAG
			pthread_mutex_lock(&philo->share->mutex_end);
			printf("DEBUG: philo %d eating last_meal %ld.%d\n", philo->i + 1, philo->last_meal.tv_sec, philo->last_meal.tv_usec);
			printf("DEBUG: philo %d eating current_tmie %ld.%d\n", philo->i + 1, current_time.tv_sec, current_time.tv_usec);
			pthread_mutex_unlock(&philo->share->mutex_end);
		#endif
		usleep(2000);
		if (gettimeofday(&current_time, NULL))
			return (printf("fail thread %d update current_time\n", philo->i + 1));
	}
	++philo->eat_cnt;
	if (pthread_mutex_unlock(philo->right_fork))
		return (printf("fail thread %d unlock right_fork\n", philo->i + 1));
	#ifdef DEBUG_FLAG
		pthread_mutex_lock(&philo->share->mutex_end);
		printf("DEBUG: philo %d unlock right\n", philo->i + 1);
		pthread_mutex_unlock(&philo->share->mutex_end);
	#endif
	if (pthread_mutex_unlock(&philo->left_fork))
		return (printf("fail thread %d unlock left_fork\n", philo->i + 1));
	#ifdef DEBUG_FLAG
		pthread_mutex_lock(&philo->share->mutex_end);
		printf("DEBUG: philo %d unlock left\n", philo->i + 1);
		pthread_mutex_unlock(&philo->share->mutex_end);
	#endif
	return (STATE_PHILO_SLEEP);
}

void	*philo_run(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (STATE_PHILO_ERROR == philo->state)
		{
			printf("thread %d state philo error\n", philo->i + 1);
			return (NULL);
		}
		else if (STATE_PHILO_FORK == philo->state)
			philo->state = state_philo_fork(philo);
		else if (STATE_PHILO_EAT == philo->state)
			philo->state = state_philo_eat(philo);
		else if (STATE_PHILO_THINK == philo->state)
			philo->state = state_philo_think(philo);
		else if (STATE_PHILO_SLEEP == philo->state)
			philo->state = state_philo_sleep(philo);
		else if (STATE_PHILO_DIE == philo->state)
		{
			#ifdef DEBUG_FLAG
				printf("DEBUG: philo %d die\n", philo->i + 1);
			#endif
			return (NULL);
		}
		else if (STATE_PHILO_ONE == philo->state)
			philo->state = state_philo_one(philo);
	}
	return (NULL);
}
