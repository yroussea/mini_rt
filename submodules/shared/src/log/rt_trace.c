/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_trace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:26:06 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 03:31:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_LOG_INTERNAL__
#include <rt/log.h>

void	rt_trace(t_rt *rt, const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	rt_vlog(rt, RT_LOG_TRACE, fmt, args);
	va_end(args);
}
