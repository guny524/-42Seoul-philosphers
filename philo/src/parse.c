/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:13:53 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/27 14:27:06 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "parse.h"

enum e_state_philo_parse	state_philo_parse_space(char c, int *num)
{
	if ('\t' == c || '\n' == c || '\v' == c
		|| '\f' == c || '\r' == c || ' ' == c)
		return (STATE_PHILO_PARSE_SPACE);
	else if ('0' <= c && c <= '9')
	{
		*num = 10 * *num + c - '0';
		return (STATE_PHILO_PARSE_NUM);
	}
	return (STATE_PHILO_PARSE_ERROR);
}

enum e_state_philo_parse	state_philo_parse_num(char c, int *num)
{
	int	tmp;

	if ('\t' == c || '\n' == c || '\v' == c
		|| '\f' == c || '\r' == c || ' ' == c)
		return (STATE_PHILO_PARSE_FINISH);
	else if ('0' <= c && c <= '9')
	{
		tmp = 10 * *num + c - '0';
		if (tmp < *num)
			return (STATE_PHILO_PARSE_ERROR);
		*num = tmp;
		return (STATE_PHILO_PARSE_NUM);
	}
	return (STATE_PHILO_PARSE_ERROR);
}

enum e_state_philo_parse	state_philo_parse_finish(char c)
{
	if ('\t' == c || '\n' == c || '\v' == c
		|| '\f' == c || '\r' == c || ' ' == c)
		return (STATE_PHILO_PARSE_FINISH);
	return (STATE_PHILO_PARSE_ERROR);
}

int	parse_num(const char *str)
{
	enum e_state_philo_parse	state;
	int							num;

	num = 0;
	state = STATE_PHILO_PARSE_SPACE;
	while (*str)
	{
		if (STATE_PHILO_PARSE_ERROR == state)
			return (-1);
		else if (STATE_PHILO_PARSE_SPACE == state)
			state = state_philo_parse_space(*str, &num);
		else if (STATE_PHILO_PARSE_NUM == state)
			state = state_philo_parse_num(*str, &num);
		else if (STATE_PHILO_PARSE_FINISH == state)
			state = state_philo_parse_finish(*str);
		++str;
	}
	if (STATE_PHILO_PARSE_ERROR == state)
		return (-1);
	return (num);
}

int	parse(t_simul *simul, int argc, const char *argv[])
{
	int		i;
	int		res;

	*simul = (t_simul){0, {0, 0}, 0, {0, 0, 0}, 0};
	res = parse_num(argv[1]);
	if (-1 == res)
		return (-1);
	simul->num = res;
	i = 2;
	while (i < 5)
	{
		res = parse_num(argv[i]);
		if (-1 == res)
			return (-1);
		simul->time[i - 2] = res * 1000;
		++i;
	}
	if (5 == argc)
		return (0);
	res = parse_num(argv[5]);
	if (-1 == res)
		return (-1);
	simul->must_eat = res;
	return (0);
}
