/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:30:27 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/07 15:02:49 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_err.h"

t_err	empty_err(void)
{
	return ((t_err){ERR_WHO_NONE, NULL, 0, NULL});
}

int	is_err(t_err err)
{
	if (ERR_WHO_NONE == err.who
		&& NULL == err.key
		&& 0 == err.no
		&& NULL == err.where)
		return (0);
	return (1);
}

int	is_err_than_print(t_err err)
{
	if (is_err(err))
	{
		print_err(err);
		return (-1);
	}
	return (0);
}
