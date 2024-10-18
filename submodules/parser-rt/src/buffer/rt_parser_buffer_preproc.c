/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_buffer_preproc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:55:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 17:32:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <rt/features.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

#if FEAT_PARSER_COMMENTS

static int	rt_parser_buffer_preproc_comment_line(char *line)
{
	const int	remove = line[0] == '#';
	size_t		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '#')
			ft_memset(&line[i], 0, ft_strlen(&line[i]));
		i++;
	}
	return (remove);
}

static void	rt_parser_buffer_preproc_comments(t_rt_parser *parser)
{
	size_t	i;
	size_t	to_remove;
	char	*line;
	size_t	total;
	size_t	len;

	i = 0;
	to_remove = 0;
	total = 0;
	while (parser->buffer && total < parser->nlines)
	{
		line = &parser->buffer[i];
		while (!line[0])
			line++;
		len = ft_strlen(line);
		to_remove += rt_parser_buffer_preproc_comment_line(line);
		i += len;
		total++;
	}
	parser->nlines -= ft_min(parser->nlines, to_remove);
}

#else

static void	rt_parser_buffer_preproc_comments(
	__attribute__((unused)) t_rt_parser *parser
) {
}

#endif

void	rt_parser_buffer_preproc(t_rt_parser *parser)
{
	size_t	i;
	bool	in_line;

	i = 0;
	parser->nlines = 0;
	in_line = false;
	while (parser->buffer && parser->buffer[i])
	{
		if (parser->buffer[i] == '\n')
		{
			if (in_line)
				parser->nlines++;
			parser->buffer[i] = 0;
			in_line = false;
		}
		else if (!in_line && parser->buffer[i] == ' ')
			parser->buffer[i] = 0;
		else
			in_line = true;
		i++;
	}
	rt_parser_buffer_preproc_comments(parser);
}
