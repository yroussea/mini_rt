/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_uint.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:47:13 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 11:49:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_PARSER_INTERNAL__
#include <rt/parser/primitive/strtod.h>
#include <rt/parser/primitive/strtoi.h>
#include <rt/parser.h>

#define INVALID_SIGN_ERROR "unsigned integer value must be positive"

RESULT	rt_parser_prim_uint(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	RESULT		res;

	res = rt_strtoi(&slice, (int *)memory, " ");
	if (RES_OK(res))
	{
		if (*(int *)memory < 0)
		{
			res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_SIGN_ERROR, NULL));
			res.file_context.length = 1;
			res.file_context.column = 1;
			res.file_context.type = FILE_ERR_INVALID_NUMBER;
			res.file_context.possible_fix = "remove the minus sign";
		}
		else
			*size = sizeof(int);
	}
	return (res);
}
