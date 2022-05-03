/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 21:23:33 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/07 17:05:22 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_err.h"
#include "philo.h"

t_err	state_philo_fork(t_philo *philo)
{
	t_err	err;

	if (pthread_mutex_lock(&philo->left_fork))
		return ((t_err){philo->i, "mutex_lock", errno, "left_fork"});
	err = print_status(philo);
	if (is_err(err))
		return (err);
	if (NULL == philo->right_fork)
		return (set_state_ret_err(philo, STATE_PHILO_ONE, empty_err()));
	return (set_state_ret_err(philo, STATE_PHILO_EAT, empty_err()));
}

t_err	state_philo_eat(t_philo *philo)
{
	t_err			err;

	if (pthread_mutex_lock(philo->right_fork))
		return ((t_err){philo->i, "mutex_lock", errno, "right_fork"});
	err = print_status(philo);
	if (is_err(err))
		return (err);
	if (usleep(get_time_us(philo->share->time[PHILO_TIME_EAT])))
		return ((t_err){philo->i, "usleep", errno, "eat"});
	if (pthread_mutex_lock(&philo->share->mutex_end))
		return ((t_err){philo->i, "mutex_lock", errno, "eat mutex_end"});
	++philo->eat_cnt;
	if (pthread_mutex_unlock(&philo->share->mutex_end))
		return ((t_err){philo->i, "mutex_unlock", errno, "eat mutex_end"});
	if (pthread_mutex_unlock(philo->right_fork))
		return ((t_err){philo->i, "mutex_unlock", errno, "right_fork"});
	if (pthread_mutex_unlock(&philo->left_fork))
		return ((t_err){philo->i, "mutex_unlock", errno, "left_fork"});
	return (set_state_ret_err(philo, STATE_PHILO_SLEEP, empty_err()));
}

t_err	state_philo_think(t_philo *philo)
{
	t_err	err;

	if (pthread_mutex_lock(&philo->share->mutex_end))
		return ((t_err){philo->i, "mutex_lock", errno, "think"});
	if (philo->share->flag_end)
	{
		if (pthread_mutex_unlock(&philo->share->mutex_end))
			return ((t_err){philo->i, "mutex_unlock", errno, "think flag_end"});
		return (set_state_ret_err(philo, STATE_PHILO_DIE, empty_err()));
	}
	if (pthread_mutex_unlock(&philo->share->mutex_end))
		return ((t_err){philo->i, "mutex_unlock", errno, "think mutex_end"});
	err = print_status(philo);
	if (is_err(err))
		return (err);
	if (philo->i % 2 && 0 == philo->once++)
		return (set_state_ret_err(philo, STATE_PHILO_SLEEP, empty_err()));
	return (set_state_ret_err(philo, STATE_PHILO_FORK, empty_err()));
}

t_err	state_philo_sleep(t_philo *philo)
{
	t_err	err;

	err = print_status(philo);
	if (is_err(err))
		return (err);
	if (usleep(get_time_us(philo->share->time[PHILO_TIME_SLEEP])))
		return ((t_err){philo->i, "usleep", errno, "sleep"});
	return (set_state_ret_err(philo, STATE_PHILO_THINK, empty_err()));
}

t_err	state_philo_one(t_philo *philo)
{
	while (1)
	{
		if (pthread_mutex_lock(&philo->share->mutex_end))
			return ((t_err){philo->i, "mutex_lock", errno, "one mutex_end"});
		if (philo->share->flag_end)
		{
			if (pthread_mutex_unlock(&philo->share->mutex_end))
				return ((t_err){philo->i, "mutex_unlock", errno,
					"one flag_end"});
			if (pthread_mutex_unlock(&philo->left_fork))
				return ((t_err){philo->i, "mutex_unlock", errno,
					"one flag_end"});
			return (set_state_ret_err(philo, STATE_PHILO_DIE, empty_err()));
		}
		if (pthread_mutex_unlock(&philo->share->mutex_end))
			return ((t_err){philo->i, "mutex_unlock", errno, "one mutex_end"});
		usleep(1);
	}
}
