/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:53:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 16:20:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

RESULT	rt_parser_parse(t_rt_parser *parser, const char *filepath)
{
	RESULT	res;

	__attribute__((cleanup(ft_strdel))) char *buffer = NULL;
	if (parser == NULL)
		return (ERR(PARSE_ERR_NULL));
	parser->filepath = filepath;
	res = rt_parser_buffer_fill(filepath, &buffer);
	if (!RES_OK(res))
		return (res);
	parser->buffer = buffer;
	res = rt_parser_buffer_sanitize(parser);
	if (!RES_OK(res))
		return (res);
	return (res);
	// return (rt_parser_buffer_loop(parser, buffer, lines));
}
