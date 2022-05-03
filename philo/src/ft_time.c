/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:50:01 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/05 20:04:22 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

struct timeval	set_time_ms(int ms)
{
	struct timeval	ret;

	ret.tv_sec = ms / 1000;
	ret.tv_usec = (ms % 1000) * 1000;
	return (ret);
}

int	get_time_ms(struct timeval time)
{
	int	ret;

	ret = time.tv_sec * 1000;
	ret += time.tv_usec / 1000;
	return (ret);
}

suseconds_t	get_time_us(struct timeval time)
{
	suseconds_t	ret;

	ret = time.tv_sec * 1000000;
	ret += time.tv_usec;
	return (ret);
}

struct timeval	sub_time(struct timeval t1, struct timeval t2)
{
	struct timeval	ret;

	ret.tv_sec = t1.tv_sec - t2.tv_sec;
	ret.tv_usec = t1.tv_usec - t2.tv_usec;
	if (ret.tv_usec < 0)
	{
		ret.tv_usec += 1000000;
		--ret.tv_sec;
	}
	return (ret);
}

int	compare_time(struct timeval t1, struct timeval t2)
{
	if (t1.tv_sec == t2.tv_sec)
	{
		if (t1.tv_usec == t2.tv_usec)
			return (0);
		else if (t1.tv_usec > t2.tv_usec)
			return (1);
		return (-1);
	}
	else if (t1.tv_sec > t2.tv_sec)
		return (1);
	return (-1);
}
