/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_buffer_sanitize.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:13:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 17:39:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static RESULT	rt_parser_buffer_invalid_line(t_rt_parser *parser, char *line)
{
	RESULT	res;

	(void)parser;
	(void)line;
	res = ERR(PARSE_ERR_FILE);
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
	RESULT	res;
	char	*buffer;

	rt_parser_buffer_preproc(parser);
	i = 0;
	res = OK();
	if (parser->nlines == 0)
		return (ERRS(PARSE_ERR_FILE_READ, "'%s' is empty", parser->filepath));
	buffer = parser->buffer;
	while (!buffer[0])
		buffer++;
	while (i < parser->nlines && RES_OK(res))
	{
		while (!buffer[0])
			buffer++;
		rt_trace(parser->rt, "buffer line: '%s'\n", buffer);
		if (rt_parser_buffer_is_invalid(buffer))
			res = rt_parser_buffer_invalid_line(parser, buffer);
		buffer += ft_strlen(buffer);
		i++;
	}
	return (res);
}
