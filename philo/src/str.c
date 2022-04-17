/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:00:11 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/27 11:31:52 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	str_error(const char *str)
{
	int	ret;
	int	len;

	len = 1;
	ret = 0;
	while (len - ret > 0)
	{
		len = ft_strlen(str);
		if (str)
			ret = write(STDERR_FILENO, str, len);
		if (-1 == ret)
			break ;
	}
	return (-1);
}
