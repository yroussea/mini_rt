/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:36:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 04:14:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H
# undef APP_H
# ifndef __RT_APP_H__
#  define __RT_APP_H__

#  include <rt/flags.h>

typedef struct s_rt_app
{
	const char		*executable;
	const char		*name;
	t_rt_flags		flags;
}	t_rt;

int		rt_init(t_rt *rt, int argc, char **argv);
void	rt_destroy(t_rt *rt);

# endif // __RT_APP_H__
#endif // APP_H
