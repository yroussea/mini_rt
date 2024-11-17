/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_test_process.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 06:59:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 19:21:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#define NO_TEST_MODE "@ primitive parsers are not allowed in normal mode"
#define MODE_FIX "run miniRT in parser test mode with the -p flag"
#define UNKNOWN_PRIMITIVE "unknown primitive parser name"

static enum e_rt_primitive	rt_parser_line_strtoprim(const char *str)
{
	static const char	*prim_str[] = {
	[RT_PRIM_COORDS] = "coords",
	[RT_PRIM_NORMAL] = "normal",
	[RT_PRIM_COLOR] = "color",
	[RT_PRIM_INT] = "int",
	[RT_PRIM_UINT] = "uint",
	[RT_PRIM_DOUBLE] = "double",
	[RT_PRIM_UDOUBLE] = "udouble",
	[RT_PRIM_URATIO] = "uratio",
	[RT_PRIM_ANGLE] = "angle",
	[RT_PRIM_BUMPFILE] = "bumpmap",
	};
	size_t				i;

	i = 0;
	while (prim_str[i])
	{
		if (!ft_strcmp(str, prim_str[i++]))
			return (i - 1);
	}
	return (-1);
}

static RESULT	rt_parser_line_test_expand(RESULT res, const char *line)
{
	if (res.type == PARSE_ERR_FILE)
	{
		res.file_context.column += rt_parser_line_token_pos(line, 1);
	}
	return (res);
}

static RESULT	rt_parser_line_test_parse(t_rt_parser *parser,
					enum e_rt_primitive type, char **tokens, const char *line)
{
	const t_rt_primitive_parser	*primp = rt_parser_prim_get(parser, type);
	char						dummy[2048];
	size_t						dummy2;
	RESULT						res;

	if (!primp || !primp->fn)
		return (ERRS(PARSE_ERR_UNKNOWN, "unknown primitive type '%s' "
				"for token '%s'\n", rt_parser_strprim(type), tokens[1]));
	rt_trace(parser->rt, "running parse step '%s' on token '%s'\n",
		rt_parser_strprim(type), tokens[1]);
	dummy2 = 0;
	res = primp->fn(parser, tokens[1], &dummy, &dummy2);
	return (rt_parser_line_test_expand(res, line));
}

RESULT	rt_parser_line_test_process(t_rt_parser *parser, char **tokens,
					const char *line)
{
	t_rt_parser_file_context	context;
	size_t						pos;
	enum e_rt_primitive			prim;

	pos = rt_parser_line_token_pos(line, 0);
	if (parser->rt->flags.mode != RT_MODE_PARSER_TEST)
	{
		context = rt_strtod_ctx_char(pos, NO_TEST_MODE, MODE_FIX);
		context.length = ft_strlen(tokens[0]);
		context.type = FILE_ERR_INVALID_TOKEN;
		return (ERR_FILE(context));
	}
	rt_trace(parser->rt, "encountered primitive test parser for '%s'\n",
		tokens[0] + 1);
	prim = rt_parser_line_strtoprim(tokens[0] + 1);
	if (prim < 0)
	{
		context = rt_strtod_ctx_char(pos + 1, UNKNOWN_PRIMITIVE, NULL);
		context.length = ft_strlen(tokens[0] - 1);
		context.type = FILE_ERR_INVALID_TOKEN;
		return (ERR_FILE(context));
	}
	return (rt_parser_line_test_parse(parser, prim, tokens, line));
}
