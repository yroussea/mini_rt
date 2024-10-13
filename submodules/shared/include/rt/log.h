/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:34:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 03:49:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H
# undef LOG_H
# ifndef __RT_LOG_H__
#  define __RT_LOG_H__

#  include <rt/app.h>
#  include <stdarg.h>

#  define RT_LOG_DEFAULT RT_LOG_INFO

enum e_rt_log_level
{
	RT_LOG_TRACE = 0,
	RT_LOG_DEBUG,
	RT_LOG_INFO,
	RT_LOG_WARNING,
	RT_LOG_ERROR,
	_RT_LOG_SIZE,
};

#  ifdef __RT_LOG_INTERNAL__

/**
 * Prints a log message to the console, depending on the log level.
 *
 * @param rt The rt application.
 * @param level The log level, see `enum e_rt_log_level`.
 * @param fmt The format string.
 * @param args The arguments.
 */
void	rt_vlog(t_rt *rt, enum e_rt_log_level level, const char *fmt,
			va_list args);

#  endif // __RT_LOG_INTERNAL__

/**
 * Prints a log message to the console, depending on the log level.
 *
 * @param rt The rt application.
 * @param level The log level, see `enum e_rt_log_level`.
 * @param fmt The format string.
 * @param ... The arguments.
 */
void	rt_log(t_rt *rt, enum e_rt_log_level level, const char *fmt, ...)
		__attribute__((format(printf, 3, 4)));

/**
 * Prints a trace log message to the console.
 *
 * @param rt The rt application.
 * @param fmt The format string.
 * @param ... The arguments.
 */
void	rt_trace(t_rt *rt, const char *fmt, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * Prints a debug log message to the console.
 *
 * @param rt The rt application.
 * @param fmt The format string.
 * @param ... The arguments.
 */
void	rt_debug(t_rt *rt, const char *fmt, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * Prints an info log message to the console.
 *
 * @param rt The rt application.
 * @param fmt The format string.
 * @param ... The arguments.
 */
void	rt_info(t_rt *rt, const char *fmt, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * Prints a warning log message to the console.
 *
 * @param rt The rt application.
 * @param fmt The format string.
 * @param ... The arguments.
 */
void	rt_warning(t_rt *rt, const char *fmt, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * Prints an error log message to the console.
 *
 * @param rt The rt application.
 * @param fmt The format string.
 * @param ... The arguments.
 */
void	rt_error(t_rt *rt, const char *fmt, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * Prints a fatal log message to the console.
 *
 * @param rt The rt application.
 * @param fmt The format string.
 * @param ... The arguments.
 */
void	rt_fatal(t_rt *rt, const char *fmt, ...)
		__attribute__((format(printf, 2, 3)));

# endif // __RT_LOG_H__
#endif // LOG_H
