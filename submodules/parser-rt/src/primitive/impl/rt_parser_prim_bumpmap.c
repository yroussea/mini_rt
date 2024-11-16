/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_bumpmap.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:36:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 19:33:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
# include <stdio.h>

RESULT	rt_parser_prim_bumpmap(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	RESULT		res;

	(void)memory;
	(void)size;
	printf("TODO: rt_parser_prim_bumpmap('%s')\n", slice);
	res = OK();
	return (res);
}
