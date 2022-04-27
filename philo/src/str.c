/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:00:11 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/01 18:21:35 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ft_time.h>
#include "philo.h"
#include "str.h" //#

int	print_status(t_philo *philo, enum e_philo_state state)
{
	struct timeval	current_time;
	const char		*str[] = {
		"has taken taken a fork",
		"is eating",
		"is thinking",
		"is sleeping",
		"died",
	};

	if (!(philo->share->flag_end && STATE_PHILO_DIE == state))
	{
		if (pthread_mutex_lock(&philo->share->mutex_end))
			return (printf("fail thread %d print lock mutex_end\n", philo->i + 1));
		#ifdef DEBUG_FLAG
			printf("DEBUG: print philo %d lock mutex_end\n", philo->i + 1);
		#endif
	}
	if (gettimeofday(&current_time, NULL))
		return (printf("fail thread %d print gettimeofday\n", philo->i + 1));
	if (0 > printf("%dms\t%d\t%s\n", get_time_ms(sub_time(current_time,
		philo->share->start_time)), philo->i + 1, str[state]))
		return (-1);
	if (STATE_PHILO_EAT == state)
		philo->last_meal = current_time;
	#ifdef DEBUG_FLAG
		if (STATE_PHILO_EAT == state)
			printf("DEBUG: print philo %d update last_meal %ld.%d\n", philo->i + 1, current_time.tv_sec, current_time.tv_usec);
	#endif
	if (!(philo->share->flag_end && STATE_PHILO_DIE == state))
	{
		#ifdef DEBUG_FLAG
			printf("DEBUG: print philo %d unlock mutex_end\n", philo->i + 1);
		#endif
		if (pthread_mutex_unlock(&philo->share->mutex_end))
			return (printf("fail thread %d print unlock mutex_end\n", philo->i + 1));
	}
	return (0);
}
