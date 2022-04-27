/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:53:44 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/01 18:13:09 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "philo.h"
#include "debug.h" //#

int	create(t_simul *simul);
int	monitoring(t_simul *simul);
int	run_and_join(t_simul *simul);

#endif
