/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_normal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 06:16:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 16:52:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#define INVALID_NORM_ERROR "normal value must be between -1 and 1"

static RESULT	rt_parser_prim_normal_expand(RESULT res, double result,
					size_t offset, const char *orig)
{
	size_t	len;

	if (RES_OK(res) && (result > 1.0f || result < -1.0f))
	{
		len = ft_strcspn(orig + offset, " ,");
		res = ERR_FILE(rt_strtod_ctx_char(0,
					INVALID_NORM_ERROR, NULL));
		res.file_context.length = len;
		res.file_context.type = FILE_ERR_INVALID_NUMBER;
	}
	if (res.type == PARSE_ERR_FILE)
		res.file_context.column += offset;
	return (res);
}

static t_vec3d	*rt_normalize(t_vec3d *vec)
{
	t_vec3d	res;

	res = v3d_norm(vec);
	ft_memcpy(vec, &res, sizeof(t_vec3d));
	return (vec);
}

// Format %f,%f,%f
RESULT	rt_parser_prim_normal(
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
	if (RES_ERR(res) || results.x > 1.0f || results.x < -1.0f)
		return (rt_parser_prim_normal_expand(res, results.x, 0, orig));
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - 1 - orig,
					INVALID_CHAR_SEP, FIX_SEP)));
	offset = slice - orig;
	res = rt_strtod(&slice, &results.y, ",");
	if (RES_ERR(res) || results.y > 1.0f || results.y < -1.0f)
		return (rt_parser_prim_normal_expand(res, results.y, offset, orig));
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - 1 - orig,
					INVALID_CHAR_SEP, FIX_SEP)));
	offset = slice - orig;
	res = rt_strtod(&slice, &results.z, " ");
	if (RES_ERR(res) || results.z > 1.0f || results.z < -1.0f)
		return (rt_parser_prim_normal_expand(res, results.z, offset, orig));
	ft_memcpy(memory, rt_normalize(&results), sizeof(t_vec3d));
	*size = sizeof(t_vec3d);
	return (res);
}
