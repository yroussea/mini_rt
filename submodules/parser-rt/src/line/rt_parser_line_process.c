/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:45:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 23:15:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

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

static RESULT	rt_parser_line_process_tokens(t_rt_parser *parser, size_t ntok,
					char **tokens)
{
	RESULT	res;

	res = OK();
	rt_trace(parser->rt, "declared object '%s'\n", tokens[0]);
	for (size_t i = 1; i < ntok; i++)
		rt_trace(parser->rt, "declared property '%s'\n", tokens[i]);
	return (res);
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
RESULT	rt_parser_line_process(t_rt_parser *parser, char *line)
{
	RESULT	res;
	char	**tokens;
	size_t	ntok;

	res = OK();
	if (!line || !*line || ft_strlen(line) == 0)
		return (res);
	ntok = rt_parser_line_tokenize(line, NULL);
	if (ntok == 0)
		return (res);
	tokens = ft_calloc(ntok, sizeof(char *));
	if (tokens == NULL)
		return (ERRS(PARSE_ERR_ALLOC, "cannot allocate tokens"));
	ntok = rt_parser_line_tokenize(line, tokens);
	if ((int)ntok > 0)
		res = rt_parser_line_process_tokens(parser, ntok, tokens);
	while (ntok--)
		ft_strdel(&tokens[ntok]);
	free(tokens);
	return (res);
}
