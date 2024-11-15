/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_register.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:08:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/15 07:13:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
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

RESULT	rt_parser_object_register(t_rt_parser *parser,
			t_object_parser_provider_fn *fn)
{
	size_t				i;
	t_rt_object_parser	objp;
	RESULT				res;

	if (!fn)
		return (ERRS(PARSE_ERR_NULL, "cannot register an object parser with"
				"a null function pointer"));
	i = 0;
	while (parser->object_parsers[i].id)
		i++;
	if (i >= RT_PARSER_MAX_OBJECTS)
		return (ERRS(PARSE_ERR_ALLOC, ERR_OBJECT_MAX));
	ft_memset(&objp, 0, sizeof(t_rt_object_parser));
	objp.parser = parser;
	res = fn(&objp);
	if (!RES_OK(res))
		rt_debug(parser->rt, "got error while registering object '%s'\n",
			objp.id);
	if (!RES_OK(res))
		return (res);
	rt_trace(parser->rt, "registering object parser '%s'\n", objp.id);
	if (rt_parser_object_check_duplicate(parser, objp.id))
		return (ERRS(PARSE_ERR_ALLOC, ERR_OBJECT_DUPLICATE, objp.id));
	parser->object_parsers[i] = objp;
	return (OK());
}
