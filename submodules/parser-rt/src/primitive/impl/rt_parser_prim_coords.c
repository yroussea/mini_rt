/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_coords.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:05:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 05:34:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static RESULT	rt_parser_prim_coords_expand(RESULT res, size_t offset)
{
	if (res.type == PARSE_ERR_FILE)
		res.file_context.column += offset;
	return (res);
}

// Format %f,%f,%f
RESULT	rt_parser_prim_coords(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	t_vec3d		results;
	RESULT		res;
	const char	*orig = slice;
	size_t		offset;

	res = rt_strtod(&slice, &results.x, ",");
	if (RES_ERR(res))
		return (res);
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - 1 - orig,
					INVALID_CHAR_SEP, FIX_SEP)));
	offset = slice - orig;
	res = rt_strtod(&slice, &results.y, ",");
	if (RES_ERR(res))
		return (rt_parser_prim_coords_expand(res, offset));
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - 1 - orig,
					INVALID_CHAR_SEP, FIX_SEP)));
	offset = slice - orig;
	res = rt_strtod(&slice, &results.z, " ");
	if (RES_ERR(res))
		return (rt_parser_prim_coords_expand(res, offset));
	ft_memcpy(memory, &results, sizeof(t_vec3d));
	*size = sizeof(t_vec3d);
	return (res);
}
