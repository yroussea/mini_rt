/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:46:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 11:48:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_PARSER_INTERNAL__
#include <rt/parser/primitive/strtod.h>
#include <rt/parser/primitive/strtoi.h>
#include <rt/parser.h>

RESULT	rt_parser_prim_int(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	RESULT		res;

	res = rt_strtoi(&slice, (int *)memory, " ");
	if (RES_OK(res))
		*size = sizeof(int);
	return (res);
}
