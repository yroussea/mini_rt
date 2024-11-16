/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_uratio.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:47:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 20:11:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#define INVALID_SIGN_ERROR "unsigned ratio must be positive"
#define INVALID_VALUE_ERROR "unsigned ratio must be between 0 and 1"

RESULT	rt_parser_prim_uratio(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	RESULT		res;
	double		value;
	const char	*orig = slice;

	res = rt_strtod(&slice, (double *)memory, " ");
	if (RES_OK(res))
	{
		value = *(double *)memory;
		if (value < 0. || value > 1.)
		{
			res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_VALUE_ERROR, NULL));
			res.file_context.length = ft_strlen(orig);
			if (value < 0.)
			{
				res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_SIGN_ERROR, NULL));
				res.file_context.possible_fix = "remove the minus sign";
				res.file_context.length = 1;
			}
			res.file_context.column = 1;
			res.file_context.type = FILE_ERR_INVALID_NUMBER;
		}
		else
			*size = sizeof(double);
	}
	return (res);
}
