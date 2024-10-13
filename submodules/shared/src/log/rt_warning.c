/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_warning.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:45:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 03:29:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_LOG_INTERNAL__
#include <rt/log.h>

void	rt_warning(t_rt *rt, const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	rt_vlog(rt, RT_LOG_WARNING, fmt, args);
	va_end(args);
}
