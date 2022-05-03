/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:53:44 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/07 15:48:33 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "philo.h"
# include "ft_err.h"

t_err	create(t_simul *simul);
t_err	check_anyone_die(t_simul *simul, bool *flag_finish);
t_err	monitoring(t_simul *simul);
t_err	wait_for_join(t_simul *simul, int cnt);
t_err	run_and_join(t_simul *simul);

#endif
