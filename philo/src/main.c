/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:30:59 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/01 19:05:01 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ft_time.h>
#include "main.h"
#include "str.h"
#include "parse.h"
#include "run.h"

int	init_philo(t_simul *simul, int i)
{
	if (pthread_mutex_init(&simul->philos[i].left_fork, NULL))
		return (printf("fail init left_fork\n")
			&& destroy_all(simul, i, -1));
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
	return (0);
}

/*
* destroy는 lock을 없애기 때문에 스레드들이 create 되기 전이나,
* 모든 스레드들이 join 되고 나서 호출해야 함
*/
int	destroy_all(t_simul *simul, int cnt, int ret)
{
	int	i;

	if (pthread_mutex_destroy(&simul->share->mutex_end))
		return (printf("fail destroy mutex_end\n"));
	i = -1;
	while (++i < cnt)
		if (pthread_mutex_destroy(&simul->philos[i].left_fork))
			return (printf("fail destroy %d fork\n", i + 1));
	if (simul->philos)
		free(simul->philos);
	return (ret);
}

int	init_simul(t_simul *simul, t_share *share, int argc, const char *argv[])
{
	int	cnt;

	memset(simul, 0, sizeof(t_simul));
	memset(share, 0, sizeof(t_share));
	simul->share = share;
	if (parse(simul, argc, argv))
		return (printf("error parse\n"));
	if (0 == simul->num)
		return (printf("no philosophers\n"));
	if (pthread_mutex_init(&share->mutex_end, NULL))
		return (printf("fail init mutex_end\n"));
	share->flag_end = false;
	simul->philos = malloc(sizeof(t_philo) * simul->num);
	if (NULL == simul->philos)
		return (printf("fail malloc\n") && destroy_all(simul, 0, -1));
	cnt = -1;
	while (++cnt < simul->num)
		if (init_philo(simul, cnt))
			return (-1);
	return (0);
}

int	init_time(t_simul *simul)
{
	int	i;

	if (gettimeofday(&simul->share->start_time, NULL))
		return (printf("fail init time gettimeoffday\n"));
	i = -1;
	while (++i < simul->num)
		simul->philos[i].last_meal = simul->share->start_time;
	return (0);
}

int	main(int argc, const char *argv[])
{
	t_simul	simul;
	t_share	share;

	if (5 != argc && 6 != argc)
		return (printf("usage: ./philo philos_num time_to_die time_to_eat \
time_to_sleep [num_of_must_eat]\n"));
	if (init_simul(&simul, &share, argc, argv))
		return (-1);
	if (init_time(&simul))
		return (-1);
	if (run_and_join(&simul))
		return (-1);
	return (destroy_all(&simul, simul.num, 0));
}
