/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 06:38:07 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 16:37:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/color.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser/primitive/strtod.h>
#include <rt/parser/primitive/strtoi.h>
#include <rt/parser.h>

#define INVALID_COLLOR  "color value is out of range (0-255)"

static RESULT	rt_parser_prim_color_expand(RESULT res, int color,
					size_t offset)
{
	if (RES_OK(res))
	{
		if (color < 0 || color > 255)
		{
			res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_COLLOR, 0));
			res.file_context.length = ft_lllen(color);
		}
	}
	if (res.type == PARSE_ERR_FILE)
		res.file_context.column += offset;
	return (res);
}

static RESULT	rt_parser_prim_color_write(RESULT res, t_vec3d *memory,
					int *color, size_t *size)
{
	memory->x = ((double)color[0]) / 255.0;
	memory->y = ((double)color[1]) / 255.0;
	memory->z = ((double)color[2]) / 255.0;
	memory->w = 1.0;
	*size = sizeof(t_vec3d);
	return (res);
}

RESULT	rt_parser_prim_color(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	int			results[3];
	RESULT		res;
	const char	*orig = slice;
	size_t		offset;

	res = rt_strtoi(&slice, &results[0], ",");
	if (RES_ERR(res) || results[0] < 0 || results[0] > 255)
		return (rt_parser_prim_color_expand(res, results[0], 0));
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - 1 - orig,
					INVALID_CHAR_SEP, FIX_SEP)));
	offset = slice - orig;
	res = rt_strtoi(&slice, &results[1], ",");
	if (RES_ERR(res) || results[1] < 0 || results[1] > 255)
		return (rt_parser_prim_color_expand(res, results[1], offset));
	if (*slice++ != ',')
		return (ERR_FILE(rt_strtod_ctx_char(slice - 1 - orig,
					INVALID_CHAR_SEP, FIX_SEP)));
	offset = slice - orig;
	res = rt_strtoi(&slice, &results[2], " ");
	if (RES_ERR(res) || results[2] < 0 || results[2] > 255)
		return (rt_parser_prim_color_expand(res, results[2], offset));
	return (rt_parser_prim_color_write(res, (t_vec3d *)memory, results, size));
}
