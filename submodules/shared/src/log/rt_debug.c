/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:45:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 03:50:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_LOG_INTERNAL__
#include <rt/log.h>

void	rt_debug(const t_rt *rt, const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	rt_vlog(rt, RT_LOG_DEBUG, fmt, args);
	va_end(args);
}
