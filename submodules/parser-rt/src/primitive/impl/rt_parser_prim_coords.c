/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_coords.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:05:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/15 07:02:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

// Format %f,%f,%f
RESULT	rt_parser_prim_position(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	double		results[3];
	RESULT		res;
	const char	*orig;

	orig = slice;
	res = rt_strtod(&slice, &results[0], ",");
	if (RES_ERR(res))
		return (res);
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - orig, INVALID_CHAR_SEP,
					FIX_SEP)));
	res = rt_strtod(&slice, &results[1], ",");
	if (RES_ERR(res))
		return (res);
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - orig, INVALID_CHAR_SEP,
					FIX_SEP)));
	res = rt_strtod(&slice, &results[2], " ");
	if (RES_ERR(res))
		return (res);
	*((double **)memory) = results;
	*size = sizeof(double) * 3;
	return (res);
}
