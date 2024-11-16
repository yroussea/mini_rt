/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_angle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:30:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 14:06:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#define INVALID_ANGLE_ERROR "angle value must be between 0 and 180"

RESULT	rt_parser_prim_angle(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	RESULT		res;
	const char	*orig = slice;

	res = rt_strtod(&slice, (double *)memory, " ");
	if (RES_OK(res))
	{
		if (*(double *)memory < 0.0 || *(double *)memory > 180.0)
		{
			res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_ANGLE_ERROR, 0));
			res.file_context.length = ft_strlen(orig);
		}
		else
			*size = sizeof(double);
	}
	return (res);
}
