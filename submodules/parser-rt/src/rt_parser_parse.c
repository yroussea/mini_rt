/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:53:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:48:26 by yroussea         ###   ########.fr       */
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

static RESULT	rt_parser_process(t_rt_parser *parser)
{
	RESULT	res;
	size_t	i;
	size_t	max;

	res = OK();
	max = ft_ulllen(parser->nlines);
	i = 0;
	while (i < parser->nlines)
	{
		if (parser->buffer[i])
			rt_debug(parser->rt, "(%*d) '%s'\n",
				(int)max, (int)i + 1, parser->buffer[i]);
		i++;
	}
	i = 0;
	while (i < parser->nlines && RES_OK(res))
	{
		if (parser->buffer[i])
			res = rt_parser_line_process(parser, i);
		i++;
	}
	return (res);
}

#define NO_PRIM_PARSERS "no primitive parsers registered. what?"
#define NO_OBJ_PARSERS "no object parsers registered. what?"
#define MISSING_REQ_PRIM "some required primitive parsers don't exist"

static size_t	rt_parser_sanity_check_seq(t_rt_parser *parser,
					size_t index, size_t j)
{
	const t_rt_object_parser	*objp = &parser->object_parsers[index];
	size_t						i;
	const char					*name;

	i = 0;
	while (parser->primitive_parsers[i].fn)
	{
		if (parser->primitive_parsers[i].type == objp->sequence[j].type)
			return (1);
		i++;
	}
	name = objp->id;
	if (parser->name_fn)
		name = objp->parser->name_fn(objp->enum_id);
	rt_warn(parser->rt, "missing primitive parser '%s' for object '%s'\n",
		rt_parser_strprim(objp->sequence[j].type), name);
	return (0);
}

static RESULT	rt_parser_sanity_check(t_rt_parser *parser)
{
	size_t	i;
	size_t	j;
	size_t	found;

	if (!parser->primitive_parsers[0].fn)
		return (ERRS(PARSE_ERR_NULL, NO_PRIM_PARSERS));
	if (!parser->object_parsers[0].id)
		return (ERRS(PARSE_ERR_NULL, NO_OBJ_PARSERS));
	i = 0;
	while (parser->object_parsers[i].id)
	{
		found = 0;
		j = 0;
		while (j < parser->object_parsers[i].sequence_size)
		{
			found += rt_parser_sanity_check_seq(parser, i, j);
			j++;
		}
		if (found != j)
			return (ERRS(PARSE_ERR_BAD_USAGE, MISSING_REQ_PRIM));
		i++;
	}
	return (OK());
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
