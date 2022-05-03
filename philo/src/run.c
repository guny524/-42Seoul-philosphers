/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:53:31 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/08 15:22:22 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "run.h"
#include "main.h"
#include "ft_time.h"

t_err	create(t_simul *simul)
{
	int	i;

	i = 0;
	while (i < simul->num)
	{
		if (pthread_create(&simul->philos[i].thread, NULL, philo_run,
				&simul->philos[i]))
			return ((t_err){i, "pthread_create", errno, "create"});
		++i;
	}
	return (empty_err());
}

t_err	check_anyone_die(t_simul *simul, bool *flag_finish)
{
	struct timeval	current;
	int				i;
	struct timeval	subtime;
	int				sub;

	i = -1;
	while (++i < simul->num)
	{
		if (pthread_mutex_lock(&simul->share->mutex_end))
			return ((t_err){ERR_WHO_MAIN, "mutex_lock", errno, "die"});
		if (simul->share->must_eat
			&& simul->philos[i].eat_cnt < simul->share->must_eat)
			*flag_finish = false;
		if (gettimeofday(&current, NULL))
			return ((t_err){ERR_WHO_MAIN, "gettimeofday", errno, "die"});
		subtime = sub_time(current, simul->philos[i].last_meal);
		if (compare_time(subtime, simul->share->time[PHILO_TIME_DIE]) > 0)
		{
			simul->share->flag_end = true;
			sub = get_time_ms(sub_time(current, simul->share->start_time));
			printf("%dms\t%d\tdied\n", sub, i + 1);
			if (pthread_mutex_unlock(&simul->share->mutex_end))
				return ((t_err){ERR_WHO_MAIN, "mutex_unlock", errno, "dieing"});
			return (empty_err());
		}
		if (pthread_mutex_unlock(&simul->share->mutex_end))
			return ((t_err){ERR_WHO_MAIN, "mutex_unlock", errno, "die"});
	}
	return (empty_err());
}

t_err	monitoring(t_simul *simul)
{
	bool	flag_finish;
	t_err	err;

	while (1)
	{
		flag_finish = true;
		err = check_anyone_die(simul, &flag_finish);
		if (is_err(err))
			return (err);
		if (pthread_mutex_lock(&simul->share->mutex_end))
			return ((t_err){ERR_WHO_MAIN, "mutex_lock", errno, "out flag"});
		if (simul->share->flag_end)
		{
			if (pthread_mutex_unlock(&simul->share->mutex_end))
				return ((t_err){ERR_WHO_MAIN, "mutex_unlock", errno, "flag"});
			return (empty_err());
		}
		if (pthread_mutex_unlock(&simul->share->mutex_end))
			return ((t_err){ERR_WHO_MAIN, "mutex_unlock", errno, "out flag"});
		if (simul->share->must_eat && flag_finish)
		{
			if (pthread_mutex_lock(&simul->share->mutex_end))
				return ((t_err){ERR_WHO_MAIN, "mutex_lock", errno, "monit"});
			simul->share->flag_end = true;
			if (pthread_mutex_unlock(&simul->share->mutex_end))
				return ((t_err){ERR_WHO_MAIN, "mutex_unlock", errno, "monit"});
			return (empty_err());
		}
		usleep(1);
	}
}

t_err	wait_for_join(t_simul *simul, int cnt)
{
	int		i;
	t_err	err;

	i = -1;
	while (++i < cnt)
	{
		if (pthread_join(simul->philos[i].thread, NULL))
		{
			err = destroy_all(simul, i);
			if (is_err(err))
				return (err);
			return ((t_err){i, "pthread_join", errno, "run_and_join"});
		}
	}
	return (empty_err());
}

t_err	run_and_join(t_simul *simul)
{
	t_err	err;
	t_err	err2;

	err = create(simul);
	if (is_err(err))
	{
		err2 = wait_for_join(simul, err.who);
		if (is_err(err2))
			return (err2);
		err2 = destroy_all(simul, err.who);
		if (is_err(err2))
			return (err2);
		return (err);
	}
	err = monitoring(simul);
	if (is_err(err))
		return (err);
	err = wait_for_join(simul, simul->num);
	if (is_err(err))
		return (err);
	return (empty_err());
}
