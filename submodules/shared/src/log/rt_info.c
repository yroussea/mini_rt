/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:30:26 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 03:30:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_LOG_INTERNAL__
#include <rt/log.h>

void	rt_info(t_rt *rt, const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	rt_vlog(rt, RT_LOG_INFO, fmt, args);
	va_end(args);
}
