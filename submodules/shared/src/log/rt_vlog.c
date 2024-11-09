/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vlog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:19:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 03:50:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#define __RT_LOG_INTERNAL__
#include <rt/log.h>
#include <stdlib.h>
#include <unistd.h>

#define NO_ALLOC_ERROR	"rt: rt_vlog: allocation error\n"
#define TARGET_FD			STDERR_FILENO

static const char	*rt_log_colors(enum e_rt_log_level level)
{
	static const char	*colors[] = {
	[RT_LOG_TRACE] = DARK_GRAY,
	[RT_LOG_DEBUG] = CYAN,
	[RT_LOG_INFO] = RESET,
	[RT_LOG_WARN] = YELLOW,
	[RT_LOG_ERROR] = RED,
	};

	if (level >= _RT_LOG_SIZE)
		return ("");
	return (colors[level]);
}

void	rt_vlog(const t_rt *rt, enum e_rt_log_level level, const char *fmt,
		va_list args)
{
	char	*msg;

	if (RT_LOG_DEFAULT - (int)rt->flags.verbosity > (int)level)
		return ;
	msg = ft_vformat(fmt, args);
	if (!msg)
	{
		(void) !write(STDERR_FILENO, NO_ALLOC_ERROR, sizeof(NO_ALLOC_ERROR));
		return ;
	}
	ft_putstr_fd(rt_log_colors(level), TARGET_FD);
	ft_putstr_fd(rt->name, TARGET_FD);
	ft_putstr_fd(": ", TARGET_FD);
	ft_putstr_fd(msg, TARGET_FD);
	ft_putstr_fd(RESET, TARGET_FD);
	free(msg);
}
