/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:53:31 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/01 21:05:47 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //# usleep
#include <stdbool.h>
#include "run.h"
#include "main.h"
#include "ft_time.h"
#include "str.h"

int	create(t_simul *simul)
{
	int	i;

	i = 0;
	while (i < simul->num)
	{
		if (pthread_create(&simul->philos[i].thread, NULL, philo_run,
			&simul->philos[i]))
			return (i);
		++i;
	}
	return (simul->num);
}

int	monitoring(t_simul *simul)
{
	int				i;
	struct timeval	current_time;
	bool			flag_finish;

	while (1)
	{
		flag_finish = true;
		i = -1;
		if (pthread_mutex_lock(&simul->share->mutex_end))
			return (printf("fail main lock mutex_end\n"));
		#ifdef DEBUG_FLAG
			printf("DEBUG: main lock mutex_end\n");
		#endif
		while (++i < simul->num)
		{
			if (simul->share->must_eat
				&& simul->philos[i].eat_cnt < simul->share->must_eat)
				flag_finish = false;
			if (gettimeofday(&current_time, NULL))
				return (printf("fail main %d gettimeofday\n", i + 1));
			#ifdef DEBUG_FLAG
				printf("DEBUG: main %d philo last_meal %ld.%d\n", i + 1, simul->philos[i].last_meal.tv_sec, simul->philos[i].last_meal.tv_usec);
				printf("DEBUG: main %d current time %ld.%d\n", i + 1, current_time.tv_sec, current_time.tv_usec);
				struct timeval	tmp = sub_time(current_time, simul->philos[i].last_meal);
				printf("DEBUG: main %d sub result %ld.%d\n", i + 1, tmp.tv_sec, tmp.tv_usec);
				printf("DEBUG: main %d compare result %d\n", i + 1, compare_time(sub_time(current_time, simul->philos[i].last_meal), simul->share->time[PHILO_TIME_DIE]));
			#endif
			if (compare_time(sub_time(current_time, simul->philos[i].last_meal),
				simul->share->time[PHILO_TIME_DIE]) > 0)
			{
				simul->share->flag_end = true;
				#ifdef DEBUG_FLAG
					printf("set flag_end\n");
				#endif
				if (print_status(&simul->philos[i], STATE_PHILO_DIE))
					return (printf("fail main %d print status\n", i + 1));
				if (pthread_mutex_unlock(&simul->share->mutex_end))
					return (printf("fail main unlock mutex_end\n"));
				return (0);
			}
		}
		if (simul->share->must_eat && flag_finish) //#
		{
			simul->share->flag_end = true;
			#ifdef DEBUG_FLAG
				printf("set flag_end\n");
			#endif
			if (pthread_mutex_unlock(&simul->share->mutex_end))
				return (printf("fail main unlock mutex_end\n"));
			return (0);
		}
		if (pthread_mutex_unlock(&simul->share->mutex_end))
			return (printf("fail main unlock mutex_end\n"));
		usleep(2000);
	}
}

int	run_and_join(t_simul *simul)
{
	int		i;
	int		created;

	created = create(simul);
	if (created == simul->num)
		monitoring(simul);
	i = -1;
	#ifdef DEBUG_FLAG
		pthread_mutex_lock(&simul->share->mutex_end);
		printf("DEBUG: main join start\n");
		pthread_mutex_unlock(&simul->share->mutex_end);
	#endif
	while (++i < created)
		if (pthread_join(simul->philos[i].thread, NULL))
		{
			#ifdef DEBUG_FLAG
				pthread_mutex_lock(&simul->share->mutex_end);
				printf("DEBUG: main join fail\n");
				pthread_mutex_unlock(&simul->share->mutex_end);
			#endif
			return (printf("fail thread %d join\n", i + 1)
				&& destroy_all(simul, created, -1));
		}
	if (created != simul->num)
		return (printf("fail thread %d create\n", created + 1)
			&& destroy_all(simul, created, -1));
	#ifdef DEBUG_FLAG
		printf("DEBUG: main run_and_join finish\n");
	#endif
	return (0);
}
