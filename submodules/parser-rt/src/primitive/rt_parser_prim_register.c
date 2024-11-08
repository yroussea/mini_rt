/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_register.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:17:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/09 00:23:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#define ERR_PRIM_DUPLICATE "primitive parser '%s' already registered"
#define ERR_PRIM_MAX "parser exceeds maximum number of primitive parsers"

static bool	rt_parser_prim_check_duplicate(t_rt_parser *parser,
			enum e_rt_primitive type)
{
	size_t	i;

	i = 0;
	while (parser->primitive_parsers[i].fn)
	{
		if (parser->primitive_parsers[i].type == type)
			return (true);
		i++;
	}
	return (false);
}

RESULT	rt_parser_prim_register(t_rt_parser *parser, enum e_rt_primitive type,
			t_rt_primitive_parser_func *fn)
{
	const char	*str = rt_parser_strprim(type);
	size_t		i;

	rt_trace(parser->rt, "registering primitive parser '%s'\n", str);
	if (rt_parser_prim_check_duplicate(parser, type))
		return (ERRS(PARSE_ERR_ALLOC, ERR_PRIM_DUPLICATE, str));
	i = 0;
	while (parser->primitive_parsers[i].fn)
		i++;
	if (i >= RT_PARSER_MAX_PRIMITIVES)
		return (ERRS(PARSE_ERR_ALLOC, ERR_PRIM_MAX));
	parser->primitive_parsers[i].type = type;
	parser->primitive_parsers[i].fn = fn;
	return (OK());
}
