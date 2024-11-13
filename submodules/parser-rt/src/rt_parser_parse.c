/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:53:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 06:52:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static RESULT	rt_err_expand(RESULT res, const char *filepath)
{
	if (res.type != PARSE_ERR_FILE)
		return (res);
	res.file_context.filename = filepath;
	return (res);
}

static void	rt_parser_buffer_dump(t_rt_parser *parser)
{
	size_t	i;
	size_t	max;

	max = ft_ulllen(parser->nlines);
	i = 0;
	while (i < parser->nlines)
	{
		if (parser->buffer[i])
			rt_debug(parser->rt, "(%*d) '%s'\n",
				(int)max, (int)i + 1, parser->buffer[i]);
		i++;
	}
}

static RESULT	rt_parser_sanity_check(t_rt_parser *parser)
{
	if (!parser->primitive_parsers[0].fn)
		return (ERRS(PARSE_ERR_NULL, "no primitive parsers registered. what?"));
	if (!parser->object_parsers[0].id)
		return (ERRS(PARSE_ERR_NULL, "no object parsers registered. what?"));
	return (OK());
}

static RESULT	rt_parser_process(t_rt_parser *parser)
{
	RESULT	res;
	size_t	i;

	res = OK();
	rt_parser_buffer_dump(parser);
	i = 0;
	while (i < parser->nlines && RES_OK(res))
	{
		if (parser->buffer[i])
			res = rt_parser_line_process(parser, i);
		i++;
	}
	return (res);
}

RESULT	rt_parser_parse(t_rt_parser *parser, const char *filepath)
{
	RESULT	res;

	if (parser == NULL)
		return (ERR(PARSE_ERR_NULL));
	res = rt_parser_sanity_check(parser);
	if (RES_OK(res))
		res = rt_parser_buffer_fill(parser, filepath);
	if (RES_OK(res))
		res = rt_parser_buffer_preproc(parser, parser->read_buffer);
	if (RES_OK(res))
		res = rt_parser_buffer_sanitize(parser);
	if (RES_OK(res))
		res = rt_parser_process(parser);
	if (!RES_OK(res))
		return (rt_err_expand(res, filepath));
	return (res);
}
