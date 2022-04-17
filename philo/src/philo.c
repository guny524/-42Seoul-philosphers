/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:30:59 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/27 14:31:46 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "str.h"
#include "parse.h"

// int	setting_table()
// {

// }

#include <stdio.h> //#

int	main(int argc, const char *argv[])
{
	t_simul	simul;

	if (5 != argc && 6 != argc)
		return (str_error("usage: ./philo philos_num time_to_die \
time_to_eat time_to_sleep [num_of_must_eat]\n"));
	if (-1 == parse(&simul, argc, argv))
		return (str_error("error parse\n"));
	printf("num: %d\n", simul.num);
	printf("die: %d\n", simul.time[PHILO_TIME_DIE]);
	printf("eat: %d\n", simul.time[PHILO_TIME_EAT]);
	printf("sleep: %d\n", simul.time[PHILO_TIME_SLEEP]);
	printf("must eat: %d\n", simul.must_eat);
	// pthread_create(.);
	if (-1 == gettimeofday(&simul.time_start, NULL))
		return (str_error("error gettimeoffday\n"));
	return (0);
}
