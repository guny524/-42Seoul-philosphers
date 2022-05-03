/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:55:36 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/08 15:15:33 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "philo.h"
# include "ft_err.h"

/*
* main.c
*/
t_err	init_philo(t_simul *simul, int i);
t_err	destroy_all(t_simul *simul, int cnt);
t_err	init_simul(t_simul *simul, int argc, const char *argv[]);
t_err	init_time(t_simul *simul);

#endif
