/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_coords.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:05:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 05:12:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

// Format %f,%f,%f
RESULT	rt_parser_prim_coords(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	t_vec3d		results;
	RESULT		res;
	const char	*orig;

	orig = slice;
	res = rt_strtod(&slice, &results.x, ",");
	if (RES_ERR(res))
		return (res);
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - orig, INVALID_CHAR_SEP,
					FIX_SEP)));
	res = rt_strtod(&slice, &results.y, ",");
	if (RES_ERR(res))
		return (res);
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - orig, INVALID_CHAR_SEP,
					FIX_SEP)));
	res = rt_strtod(&slice, &results.z, " ");
	if (RES_ERR(res))
		return (res);
	ft_memcpy(memory, &results, sizeof(t_vec3d));
	*size = sizeof(t_vec3d);
	return (res);
}
