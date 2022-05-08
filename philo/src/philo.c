/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:51:23 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/08 16:09:06 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"
#include "ft_time.h"
#include "ft_err.h"

t_err	set_state_ret_err(t_philo *philo, enum e_philo_state state, t_err err)
{
	philo->state = state;
	return (err);
}

t_err	print_status(t_philo *philo)
{
	struct timeval	current;
	const char		*str[] = {
		"has taken a fork", "is eating", "is thinking", "is sleeping"};
	int				sub;

	if (pthread_mutex_lock(&philo->share->mutex_end))
		return ((t_err){philo->i, "mutex_lock", errno, "print-mutex_end"});
	if (philo->share->flag_end)
	{
		if (pthread_mutex_unlock(&philo->share->mutex_end))
			return ((t_err){philo->i, "mutex_unlock", errno, "print-flag_end"});
		return (empty_err());
	}
	if (gettimeofday(&current, NULL))
		return ((t_err){philo->i, "gettimeofday", errno, "print-gettimeofday"});
	sub = get_time_ms(sub_time(current, philo->share->start_time));
	if (0 > printf("%dms\t%d\t%s\n", sub, philo->i + 1, str[philo->state]))
		return ((t_err){philo->i, "printf", errno, "print-printf"});
	if (STATE_PHILO_EAT == philo->state)
		philo->last_meal = current;
	if (pthread_mutex_unlock(&philo->share->mutex_end))
		return ((t_err){philo->i, "mutex_unlock", errno, "print-mutex_end"});
	return (empty_err());
}

void	*state_philo_error(t_philo *philo, t_err err)
{
	pthread_mutex_lock(&philo->share->mutex_end);
	philo->share->flag_end = true;
	print_err(err);
	pthread_mutex_unlock(&philo->share->mutex_end);
	return (NULL);
}

void	*philo_run(void *arg)
{
	t_philo	*philo;
	t_err	err;

	philo = (t_philo *)arg;
	err = empty_err();
	while (1)
	{
		if (is_err(err))
			return (state_philo_error(philo, err));
		else if (STATE_PHILO_FORK == philo->state)
			err = state_philo_fork(philo);
		else if (STATE_PHILO_EAT == philo->state)
			err = state_philo_eat(philo);
		else if (STATE_PHILO_THINK == philo->state)
			err = state_philo_think(philo);
		else if (STATE_PHILO_SLEEP == philo->state)
			err = state_philo_sleep(philo);
		else if (STATE_PHILO_DIE == philo->state)
			return (NULL);
		else if (STATE_PHILO_ONE == philo->state)
			err = state_philo_one(philo);
	}
	return (NULL);
}
