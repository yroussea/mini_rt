/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:53:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/31 08:19:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static RESULT	rt_err_expand(RESULT res, const char *filepath)
{
	if (res.type != PARSE_ERR_FILE)
		return (res);
	res.file_context.filename = filepath;
	return (res);
}

RESULT	rt_parser_parse(t_rt_parser *parser, const char *filepath)
{
	RESULT	res;

	__attribute__((cleanup(ft_strdel))) char *buffer = NULL;
	if (parser == NULL)
		return (ERR(PARSE_ERR_NULL));
	res = rt_parser_buffer_fill(filepath, &buffer, &parser->nlines);
	if (RES_OK(res))
		res = rt_parser_buffer_preproc(parser, buffer);
	if (RES_OK(res))
		res = rt_parser_buffer_sanitize(parser);
	if (!RES_OK(res))
		return (rt_err_expand(res, filepath));
	return (res);
	// return (rt_parser_buffer_loop(parser, buffer, lines));
}
