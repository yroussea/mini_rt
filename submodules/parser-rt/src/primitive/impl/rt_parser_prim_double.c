/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_double.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 06:56:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 03:57:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

RESULT	rt_parser_prim_double(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	RESULT	res;

	rt_trace(parser->rt, "parsing double from '%s'\n", slice);
	res = rt_strtod(&slice, (double *)memory, " ");
	rt_trace(parser->rt, "parsed double from '%s' to %f\n", slice,
		*((double *)memory));
	if (RES_OK(res))
		*size = sizeof(double);
	return (res);
}
