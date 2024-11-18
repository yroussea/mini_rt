/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_finalize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:41:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:54:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static bool	rt_parser_has_object(t_rt_parser *parser, size_t enum_id)
{
	t_list	*list;
	size_t	*object;

	list = parser->result;
	while (list)
	{
		object = (size_t *)list->content;
		if (*object == enum_id)
			return (true);
		list = list->next;
	}
	return (false);
}

static bool	rt_parser_finalize_should_apply(t_rt_parser *parser)
{
	size_t	i;
	char	*line;

	if (parser->rt->flags.mode != RT_MODE_PARSER_TEST)
		return (true);
	i = 0;
	while (i < parser->nlines)
	{
		if (parser->buffer[i])
		{
			line = parser->buffer[i];
			line += ft_strspn(line, " ");
			if (line[0] == '@')
				return (false);
		}
		i++;
	}
	return (true);
}

RESULT	rt_parser_finalize(t_rt_parser *parser)
{
	size_t	i;

	if (!rt_parser_finalize_should_apply(parser))
		return (OK());
	i = 0;
	while (parser->object_parsers[i].id)
	{
		if (parser->object_parsers[i].is_required)
		{
			rt_trace(parser->rt, "checking for required object '%s'\n",
				parser->object_parsers[i].id);
			if (!rt_parser_has_object(parser,
					parser->object_parsers[i].enum_id))
				return (ERRS(PARSE_ERR_MISSING_REQUIRED,
						"missing required object '%s'",
						parser->object_parsers[i].id));
		}
		i++;
	}
	return (OK());
}
