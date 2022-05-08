/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:53:44 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/08 15:55:08 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "philo.h"
# include "ft_err.h"

/*
* run.c
*/
t_err	create(t_simul *simul);
t_err	check_anyone_die(t_simul *simul, bool *flag_finish);
t_err	monitoring(t_simul *simul);
t_err	wait_for_join(t_simul *simul, int cnt);
t_err	run_and_join(t_simul *simul);

/*
* run2.c
*/
t_err	set_flag_end_true(t_simul *simul);
t_err	set_flag_end_true_die(t_simul *simul, struct timeval current, int i);

#endif
