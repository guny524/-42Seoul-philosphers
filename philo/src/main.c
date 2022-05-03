/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:30:59 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/08 15:21:13 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "parse.h"
#include "run.h"
#include "ft_time.h"
#include "ft_err.h"

t_err	init_philo(t_simul *simul, int i)
{
	t_err	err;

	if (pthread_mutex_init(&simul->philos[i].left_fork, NULL))
	{
		err = destroy_all(simul, i);
		if (is_err(err))
			return (err);
		return ((t_err){i, "mutex_init", errno, "left_fork"});
	}
	if (1 == simul->num)
		simul->philos[i].right_fork = NULL;
	else
		simul->philos[i].right_fork = \
			&simul->philos[(i + 1) % simul->num].left_fork;
	simul->philos[i].i = i;
	simul->philos[i].state = STATE_PHILO_THINK;
	simul->philos[i].share = simul->share;
	simul->philos[i].eat_cnt = 0;
	simul->philos[i].once = 0;
	return (empty_err());
}

/*
* destroy는 lock을 없애기 때문에 스레드들이 create 되기 전이나,
* 모든 스레드들이 join 되고 나서 호출해야 함
*/
t_err	destroy_all(t_simul *simul, int cnt)
{
	int	i;

	if (pthread_mutex_destroy(&simul->share->mutex_end))
		return ((t_err){ERR_WHO_MAIN, "mutex_destroy", errno, "mutex_end"});
	i = -1;
	while (++i < cnt)
		if (pthread_mutex_destroy(&simul->philos[i].left_fork))
			return ((t_err){i, "mutex_destroy", errno, "left_fork"});
	if (simul->philos)
		free(simul->philos);
	return (empty_err());
}

t_err	init_simul(t_simul *simul, int argc, const char *argv[])
{
	int		cnt;
	t_err	err;

	if (parse(simul, argc, argv))
		return ((t_err){ERR_WHO_MAIN, "parse", 0, "init_simul"});
	if (0 == simul->num)
		return ((t_err){ERR_WHO_MAIN, "num", 0, "init_simul"});
	if (pthread_mutex_init(&simul->share->mutex_end, NULL))
		return ((t_err){ERR_WHO_MAIN, "mutex_init", errno, "mutex_end"});
	simul->philos = malloc(sizeof(t_philo) * simul->num);
	if (NULL == simul->philos)
	{
		err = destroy_all(simul, 0);
		if (is_err(err))
			return (err);
		return ((t_err){ERR_WHO_MAIN, "malloc", errno, "init_simul"});
	}
	cnt = -1;
	while (++cnt < simul->num)
	{
		err = init_philo(simul, cnt);
		if (is_err(err))
			return (err);
	}
	return (empty_err());
}

t_err	init_time(t_simul *simul)
{
	int	i;

	if (gettimeofday(&simul->share->start_time, NULL))
		return ((t_err){ERR_WHO_MAIN, "gettimeofday", errno, "init_time"});
	i = -1;
	while (++i < simul->num)
		simul->philos[i].last_meal = simul->share->start_time;
	return (empty_err());
}

int	main(int argc, const char *argv[])
{
	t_simul	simul;
	t_share	share;

	if (5 != argc && 6 != argc)
		return (printf("usage: ./philo philos_num time_to_die time_to_eat \
time_to_sleep [num_of_must_eat]\n"));
	memset(&simul, 0, sizeof(t_simul));
	memset(&share, 0, sizeof(t_share));
	simul.share = &share;
	share.flag_end = false;
	if (is_err_than_print(init_simul(&simul, argc, argv)))
		return (-1);
	if (is_err_than_print(init_time(&simul)))
		return (-1);
	if (is_err_than_print(run_and_join(&simul)))
		return (-1);
	return (is_err_than_print(destroy_all(&simul, simul.num)));
}
