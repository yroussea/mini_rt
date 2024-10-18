/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_errs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:34:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 02:11:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <rt/parser/error.h>

__attribute__((always_inline))
t_rt_parse_error	rt_parse_errs(enum e_rt_parse_error type,
						const char *string_data, ...)
{
	va_list				args;
	const char			*str;

	va_start(args, string_data);
	str = ft_vformat(string_data, args);
	va_end(args);
	if (str == NULL)
		return (ERR(type));
	return (ERRD(type, (void *) str));
}
