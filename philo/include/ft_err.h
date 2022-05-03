/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:11:05 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/08 15:14:13 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERR_H
# define FT_ERR_H

# include <sys/errno.h>
# include "philo.h"

enum e_err_who
{
	ERR_WHO_NONE = -2,
	ERR_WHO_MAIN = -1,
};

typedef struct s_err
{
	enum e_err_who	who;
	char			*key;
	int				no;
	char			*where;
}	t_err;

/*
* ft_err.c
*/
char	*get_err_msg_pthread(t_err err);
char	*get_err_msg_mutex(t_err err);
char	*get_err_msg_common(t_err err);
char	*get_err_msg_main(t_err err);
void	print_err(t_err err);

/*
* ft_err2.c
*/
t_err	empty_err(void);
int		is_err(t_err err);
int		is_err_than_print(t_err err);

#endif
