/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:45:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 06:00:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static RESULT	rt_parser_line_result_expand(RESULT res, size_t index)
{
	if (res.type == PARSE_ERR_FILE)
		res.file_context.line = index + 1;
	return (res);
}

static size_t	rt_parser_line_tokenize(const char *line, char **tokens)
{
	size_t	ntok;
	size_t	i;

	ntok = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			ntok++;
			if (tokens)
				tokens[ntok - 1] = ft_strndup(line + i,
						ft_strcspn(line + i, " "));
			if (tokens && !tokens[ntok - 1])
				return ((size_t) - 1);
			i += ft_strcspn(line + i, " ");
		}
		else
			i++;
	}
	return (ntok);
}

static RESULT	rt_parser_line_validate_ntok(t_rt_parser *parser, size_t ntok,
					t_rt_object_parser *objp, char **tokens)
{
	(void)parser;
	(void)tokens;
	if (ntok >= objp->required && ntok <= objp->sequence_size)
		return (OK());
	rt_debug(parser->rt, "invalid number of tokens for '%s' - "
		"got %d, req %d, max %d\n", objp->id, (int)ntok, (int)objp->required,
		(int)objp->sequence_size);
	return (OK());
}

static RESULT	rt_parser_line_process_type(t_rt_parser *parser, size_t ntok,
					char **tokens, const char *line)
{
	size_t				i;
	size_t				size;
	t_rt_object_parser	*objp;
	t_rt_object_parser	*tmp;

	i = 0;
	size = 0;
	objp = NULL;
	tmp = NULL;
	rt_trace(parser->rt, "looking for object parser for '%s'\n", tokens[0]);
	while (parser->object_parsers[i].id)
	{
		tmp = &parser->object_parsers[i];
		if (!objp)
		{
			if (!ft_strcmp(tmp->id, tokens[0]))
				objp = tmp;
		}
		size += ft_strlen(tmp->id);
		i++;
	}
	if (objp)
		return (rt_parser_line_validate_ntok(parser, ntok, objp, tokens));
	rt_debug(parser->rt, "unknown object identifier: '%s'\n", tokens[0]);
	return (rt_parser_line_unknown_type(parser, tokens, line));
}

/**
 * @brief Processes a .rt map line.
 *
 * This function first needs to tokenize the line, then check the first token
 * for the object's type identifier. Then, it will find the corresponding
 * object parser and delegate the parsing to it.
 *
 * @param parser The parser.
 * @param line The line to process.
 *
 * @return A result.
 */
RESULT	rt_parser_line_process(t_rt_parser *parser, size_t index)
{
	const char	*line = parser->buffer[index];
	RESULT		res;
	char		**tokens;
	size_t		ntok;
	size_t		i;

	if (!line || !*line || ft_strlen(line) == 0)
		return (OK());
	ntok = rt_parser_line_tokenize(line, NULL);
	if (ntok == 0)
		return (OK());
	tokens = ft_calloc(ntok + 1, sizeof(char *));
	if (tokens == NULL)
		return (ERRS(PARSE_ERR_ALLOC, "cannot allocate tokens"));
	ntok = rt_parser_line_tokenize(line, tokens);
	if ((int)ntok > 0)
		res = rt_parser_line_process_type(parser, ntok, tokens, line);
	i = 0;
	while (tokens[i])
		ft_strdel(&tokens[i++]);
	free(tokens);
	if ((int)ntok <= 0)
		return (ERRS(PARSE_ERR_ALLOC, "cannot allocate token strings"));
	return (rt_parser_line_result_expand(res, index));
}
