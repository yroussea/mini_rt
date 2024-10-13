/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:44:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 03:29:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_LOG_INTERNAL__
#include <rt/log.h>

void	rt_error(t_rt *rt, const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	rt_vlog(rt, RT_LOG_ERROR, fmt, args);
	va_end(args);
}
