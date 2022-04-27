/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:55:36 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/01 18:07:19 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>
# include "philo.h"
#include "debug.h" //#

/*
* main.c
*/
int	init_philo(t_simul *simul, int i);
int	destroy_all(t_simul *simul, int cnt, int ret);
int	init_simul(t_simul *simul, t_share *share, int argc, const char *argv[]);
int	init_time(t_simul *simul);

#endif
