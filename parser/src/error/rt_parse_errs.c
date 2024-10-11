/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_errs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:34:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/10 23:38:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/error.h>

__attribute__((always_inline))
t_rt_parse_error	rt_parse_errs(enum e_rt_parser_error type,
						const char *string_data)
{
	return (rt_parse_errd(type, (void *)string_data));
}
