/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:14:00 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/30 15:35:31 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "philo.h"
#include "debug.h" //#

enum e_state_philo_parse
{
	STATE_PHILO_PARSE_ERROR,
	STATE_PHILO_PARSE_SPACE,
	STATE_PHILO_PARSE_NUM,
	STATE_PHILO_PARSE_FINISH,
};

enum e_state_philo_parse	state_philo_parse_space(char c, int *num);
enum e_state_philo_parse	state_philo_parse_num(char c, int *num);
enum e_state_philo_parse	state_philo_parse_finish(char c);
int							parse_num(const char *str);
int							parse(t_simul *simul, int argc, const char *argv[]);

#endif
