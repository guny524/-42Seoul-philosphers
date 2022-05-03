/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:49:24 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/08 15:14:34 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include <sys/time.h>

struct timeval	set_time_ms(int ms);
int				get_time_ms(struct timeval time);
suseconds_t		get_time_us(struct timeval time);
struct timeval	sub_time(struct timeval t1, struct timeval t2);
int				compare_time(struct timeval t1, struct timeval t2);

#endif
