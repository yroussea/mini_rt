/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_buffer_sanitize.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:13:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 21:57:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static RESULT	rt_parser_buffer_invalid_line(t_rt_parser *parser, size_t line)
{
	RESULT		res;

	(void)parser;
	res = ERR(PARSE_ERR_FILE);
	res.file_context.line = line + 1;
	res.file_context.type = FILE_ERR_NON_EMPTY_LINE;
	res.file_context.column = -1;
	res.file_context.error_message = "only spaces were found on this line";
	res.file_context.possible_fix = "clear the entire line";
	return (res);
}

static bool	rt_parser_buffer_is_invalid(const char *buffer)
{
	const size_t	len = ft_strlen(buffer);
	size_t			size;

	if (len == 0)
		return (0);
	size = 0;
	while (buffer[size])
	{
		if (!ft_isspace(buffer[size]))
			return (0);
		size++;
	}
	return (1);
}

RESULT	rt_parser_buffer_sanitize(t_rt_parser *parser)
{
	size_t	i;

	i = 0;
	while (i < parser->nlines)
	{
		if (rt_parser_buffer_is_invalid(parser->buffer[i]))
			return (rt_parser_buffer_invalid_line(parser, i));
		i++;
	}
	return (OK());
}
