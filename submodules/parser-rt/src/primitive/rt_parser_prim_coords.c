/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_coords.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:05:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/06 22:08:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser.h>
#include <rt/parser/primitive/stdtod.h>

// Format %f,%f,%f
static RESULT	rt_parser_prim_coords(t_rt_parser *parser, const char *slice,
				void *memory, size_t *size)
{
	double	results[3];
	RESULT	res;
	char	*orig;

	orig = slice;
	res = rt_stdtod(&slice, &results[0], ",");
	if (RES_ERR(res))
		return (res);
	if (*slice++ != ',')
		return (rt_strtod_ctx_char(slice - orig, INVALID_CHAR_SEP, FIX_SEP));
	res = rt_stdtod(&slice, &results[1], ",");
	if (RES_ERR(res))
		return (res);
	if (*slice++ != ',')
		return (rt_strtod_ctx_char(slice - orig, INVALID_CHAR_SEP, FIX_SEP));
	res = rt_stdtod(&slice, &results[2], "");
	if (RES_ERR(res))
		return (res);
	*((double *)memory) = results;
	*size = sizeof(double) * 3;
	return (res);
}

__attribute__((constructor))
void	rt_parser_prim_coords_init(void)
{
	rt_parser_global_primitive(RT_PRIM_COORDINATES, rt_parser_prim_coords);
}
