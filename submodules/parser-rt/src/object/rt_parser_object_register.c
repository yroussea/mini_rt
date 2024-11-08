/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_register.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:08:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/09 00:23:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#define ERR_OBJECT_DUPLICATE "object parser '%s' already registered"
#define ERR_OBJECT_MAX "parser exceeds maximum number of object parsers"

static bool	rt_parser_object_check_duplicate(t_rt_parser *parser,
			const char *type)
{
	size_t	i;

	i = 0;
	while (parser->object_parsers[i].id)
	{
		if (!ft_strcmp(parser->object_parsers[i].id, type))
			return (true);
		i++;
	}
	return (false);
}

RESULT	rt_parser_object_register(t_rt_parser *parser, t_rt_object_parser objp)
{
	size_t		i;

	rt_trace(parser->rt, "registering object parser '%s'\n", objp.id);
	if (rt_parser_object_check_duplicate(parser, objp.id))
		return (ERRS(PARSE_ERR_ALLOC, ERR_OBJECT_DUPLICATE, objp.id));
	i = 0;
	while (parser->object_parsers[i].id)
		i++;
	if (i >= RT_PARSER_MAX_OBJECTS)
		return (ERRS(PARSE_ERR_ALLOC, ERR_OBJECT_MAX));
	parser->object_parsers[i] = objp;
	return (OK());
}
