/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:45:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 01:46:12 by kiroussa         ###   ########.fr       */
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
						ft_strcspn(line + i, " \t"));
			if (tokens && !tokens[ntok - 1])
				return ((size_t) - 1);
			i += ft_strcspn(line + i, " \t");
		}
		else
			i++;
	}
	return (ntok);
}

// Note: This only validates if the number is too high.
// Missing parameters are handled later, after individual parameter parsing.
static RESULT	rt_parser_line_validate_ntok(char **tokens, size_t ntok,
					t_rt_object_parser *objp, const char *line)
{
	t_rt_parser_file_context	context;
	const char					*name;

	if (ntok - 1 <= objp->sequence_size)
		return (rt_parser_object_parse(objp, tokens, line));
	ft_memset(&context, 0, sizeof(t_rt_parser_file_context));
	context.type = FILE_ERR_TOO_MANY_PARTS;
	context.length = ft_strlen(tokens[ntok - 1]);
	context.column = rt_parser_line_token_pos(line, ntok - 1);
	context.error_message = "this parameter is unnecessary";
	name = objp->id;
	if (objp->parser->name_fn)
		name = objp->parser->name_fn(objp->enum_id);
	if (objp->sequence_size == 0)
		context.possible_fix = ft_format("object '%s' doesn't take parameters",
				name);
	else if (objp->sequence_size == 1)
		context.possible_fix = ft_format("object '%s' only accepts a "
				"single parameter", name);
	else
		context.possible_fix = ft_format("object '%s' only accepts from %d "
				"to %d parameters", name, objp->required, objp->sequence_size);
	return (ERR_FILE(context));
}

static RESULT	rt_parser_line_process_type(t_rt_parser *parser, size_t ntok,
					char **tokens, const char *line)
{
	size_t				i;
	t_rt_object_parser	*objp;
	t_rt_object_parser	*tmp;
	RESULT				res;

	i = 0;
	objp = NULL;
	tmp = NULL;
	rt_trace(parser->rt, "looking for object parser for '%s'\n", tokens[0]);
	if (tokens[0][0] == '@')
		return (rt_parser_line_test_process(parser, tokens, line));
	while (parser->object_parsers[i].id && !objp)
	{
		tmp = &parser->object_parsers[i];
		if (!ft_strcmp(tmp->id, tokens[0]))
			objp = tmp;
		i++;
	}
	if (!objp)
		return (rt_parser_line_unknown_type(parser, tokens, line));
	res = rt_parser_line_check_unique(parser, objp, line,
			(const char **)tokens);
	if (RES_OK(res))
		res = rt_parser_line_validate_ntok(tokens, ntok, objp, line);
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
