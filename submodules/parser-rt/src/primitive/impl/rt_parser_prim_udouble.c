/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_udouble.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:47:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 16:36:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#define INVALID_SIGN_ERROR "unsigned double value must be positive"

RESULT	rt_parser_prim_udouble(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	RESULT		res;

	res = rt_strtod(&slice, (double *)memory, " ");
	if (RES_OK(res))
	{
		if (*(double *)memory < 0)
		{
			res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_SIGN_ERROR, NULL));
			res.file_context.length = 1;
			res.file_context.column = 0;
			res.file_context.type = FILE_ERR_INVALID_NUMBER;
			res.file_context.possible_fix = "remove the minus sign";
		}
		else
			*size = sizeof(double);
	}
	return (res);
}
