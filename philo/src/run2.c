/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:36:30 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/08 16:15:38 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "philo.h"
#include "ft_err.h"
#include "ft_time.h"

t_err	set_flag_end_true(t_simul *simul)
{
	simul->share->flag_end = true;
	if (pthread_mutex_unlock(&simul->share->mutex_end))
		return ((t_err){ERR_WHO_MAIN, "mutex_unlock", errno, "monit"});
	return (empty_err());
}

t_err	set_flag_end_true_die(t_simul *simul, struct timeval current, int i)
{
	int	sub;

	simul->share->flag_end = true;
	sub = get_time_ms(sub_time(current, simul->share->start_time));
	if (0 > printf("%dms\t%d\tdied\n", sub, i + 1))
		return ((t_err){ERR_WHO_MAIN, "printf", errno, "print die"});
	if (pthread_mutex_unlock(&simul->share->mutex_end))
		return ((t_err){ERR_WHO_MAIN, "mutex_unlock", errno, "dieing"});
	return (empty_err());
}
