/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_buffer_preproc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:55:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/27 12:25:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <rt/features.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#if FEAT_PARSER_COMMENTS

static void	rt_parser_buffer_preproc_comments(t_rt_parser *parser)
{
	size_t	i;
	size_t	ci;

	i = 0;
	while (i < parser->nlines)
	{
		ci = ft_strcspn(parser->buffer[i], "#");
		parser->buffer[i][ci] = 0;
		i++;
	}
}

#else

__attribute__((always_inline, visibility("hidden"), searchingforstufftoputhere))
static void	rt_parser_buffer_preproc_comments(
	__attribute__((unused)) t_rt_parser *parser
) {
}

#endif

RESULT	rt_parser_buffer_preproc(t_rt_parser *parser, char *buffer)
{
	const t_rt	*rt = parser->rt;
	int			i;

	parser->buffer = ft_calloc(sizeof(char *), parser->nlines + 1);
	if (parser->buffer == NULL)
		return (ERRS(PARSE_ERR_ALLOC, "cannot allocate buffer"));
	rt_trace(rt, "buffer_preproc: reading %d lines\n", (int)parser->nlines);
	i = 0;
	while (i < (int)parser->nlines && *buffer)
	{
		parser->buffer[i++] = buffer;
		buffer[ft_strcspn(buffer, "\n")] = '\0';
		buffer += ft_strlen(buffer) + 1;
	}
	rt_parser_buffer_preproc_comments(parser);
	i = -1;
	while (++i < (int)parser->nlines)
	{
		if (ft_strlen(parser->buffer[i]) == 0)
			parser->buffer[i] = NULL;
		else
			rt_trace(rt, "buffer_preproc: buffer[%d] = '%s'\n",
				(int)i, parser->buffer[i]);
	}
	return (OK());
}
