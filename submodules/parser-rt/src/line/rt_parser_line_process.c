/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:45:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/11 23:23:00 by kiroussa         ###   ########.fr       */
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

static RESULT	rt_parser_line_unknown_type(t_rt_parser *parser, size_t ntok,
					char **tokens, size_t size_total)
{
	RESULT	res;
	char	*err_str;

	err_str = ft_calloc(size_total + ntok, sizeof(char));
	if (err_str == NULL)
		res = ERR_FILE(FILE_ERR_UNKNOWN_ID);
	else
	{
		res = ERR_FILE(FILE_ERR_UNKNOWN_ID);
	}
	ft_strdel(&err_str);
	return (res);
}

static RESULT	rt_parser_line_process_type(t_rt_parser *parser, size_t ntok,
					char **tokens)
{
	size_t				i;
	size_t				size;
	bool				found;
	t_rt_object_parser	objp;
	char				*err_str;

	i = 0;
	size = 0;
	found = false;
	while (parser->object_parsers[i].id)
	{
		if (!found)
		{
			objp = parser->object_parsers[i];
			if (!ft_strcmp(objp.id, "AA")) // tokens[0]))
				found = true;
		}
		size += ft_strlen(parser->object_parsers[i].id);
		i++;
	}
	if (found)
		return (OK());
	return (rt_parser_line_unknown_type(parser, ntok, tokens, size));
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
		res = rt_parser_line_process_type(parser, ntok, tokens);
	if ((int)ntok > 0 && RES_OK(res))
		res = rt_parser_object_parse(parser, ntok - 1, tokens);
	while (ntok--)
		ft_strdel(&tokens[ntok]);
	free(tokens);
	return (res);
}
