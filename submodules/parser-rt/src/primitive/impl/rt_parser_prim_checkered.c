/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_checkered.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:23:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 19:29:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#define INVALID_CHECKERED "expected 'checkered' (optional)"

RESULT	rt_parser_prim_checkered(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	RESULT		res;

	res = OK();
	if (!ft_strcmp(slice, "checkered"))
		((int *)memory)[0] |= CHECKERBOARD;
	else
		res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHECKERED, 0));
	if (res.type == PARSE_ERR_FILE)
		res.file_context.length = ft_strlen(slice);
	else if (RES_OK(res))
		*size = sizeof(int);
	return (res);
}
