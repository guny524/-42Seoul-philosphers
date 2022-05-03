/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:12:14 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/07 16:11:28 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_str.h"
#include "ft_err.h"

char	*get_err_msg_pthread(t_err err)
{
	if (0 == ft_strcmp(err.key, "pthread_create"))
	{
		if (35 == err.no)
			return ("total number thread exceeded");
		else if (1 == err.no)
			return ("permission scheduling policy");
		else if (22 == err.no)
			return ("invalid attribute");
	}
	else if (0 == ft_strcmp(err.key, "pthread_join"))
	{
		if (22 == err.no)
			return ("can not join cause thread already detached");
		else if (3 == err.no)
			return ("no such thread, can not find thread ID");
		else if (11 == err.no)
			return ("thread specify the calling thread, deadlock would occur");
	}
	return (NULL);
}

char	*get_err_msg_mutex(t_err err)
{
	if (0 == ft_strcmp(err.key, "mutex_init"))
	{
		if (22 == err.no)
			return ("invalid attribute");
		else if (12 == err.no)
			return ("cannot allocate memory");
	}
	else if (22 == err.no)
		return ("invalid mutex");
	else if (0 == ft_strcmp(err.key, "mutex_destroy"))
	{
		if (16 == err.no)
			return ("busy mutex is locked");
	}
	else if (0 == ft_strcmp(err.key, "mutex_lock"))
	{
		if (11 == err.no)
			return ("try to hold same lock, deadlock would occur");
	}
	else if (0 == ft_strcmp(err.key, "mutex_unlock"))
	{
		if (1 == err.no)
			return ("permission current thread does not hold this mutex");
	}
	return (NULL);
}

char	*get_err_msg_common(t_err err)
{
	if (0 == ft_strcmp(err.key, "printf"))
	{
		if (92 == err.no)
			return ("invalid character");
		else if (12 == err.no)
			return ("insufficient storage space");
	}
	else if (0 == ft_strcmp(err.key, "usleep"))
	{
		if (4 == err.no)
			return ("signal invoke catching function");
	}
	else if (0 == ft_strcmp(err.key, "gettimeofday"))
	{
		if (14 == err.no)
			return ("timeval address is invalid");
		else if (1 == err.no)
			return ("non super user set time");
	}
	return (get_err_msg_main(err));
}

char	*get_err_msg_main(t_err err)
{
	if (0 == ft_strcmp(err.key, "parse"))
		return ("parse error");
	else if (0 == ft_strcmp(err.key, "malloc"))
		return ("malloc fail");
	return (NULL);
}

void	print_err(t_err err)
{
	char	*err_msg;

	if (0 == ft_strncmp(err.key, "pthread", 7))
		err_msg = get_err_msg_pthread(err);
	else if (0 == ft_strncmp(err.key, "mutex", 5))
		err_msg = get_err_msg_mutex(err);
	else
		err_msg = get_err_msg_common(err);
	if (ERR_WHO_MAIN == err.who)
		printf("main fail %s with %s where %s\n",
			err.key, err_msg, err.where);
	else
		printf("thread %d fail %s with %s where %s\n",
			err.who + 1, err.key, err_msg, err.where);
}
