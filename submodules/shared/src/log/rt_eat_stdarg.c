/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_eat_stdarg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:27:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 00:30:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>

void	rt_eat_stdarg(const char *fmt, ...)
{
	va_list	args;

	(void)fmt;
	va_start(args, fmt);
	va_end(args);
}
