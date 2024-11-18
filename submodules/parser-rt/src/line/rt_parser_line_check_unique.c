/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_check_unique.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:19:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 19:18:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/log.h>
#include <rt/objects.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static char	*rt_parser_line_find_other(t_rt_parser *parser,
				t_rt_object_parser *objp, size_t *nline, int *column)
{
	size_t	i;
	char	*line;
	size_t	size;

	i = 0;
	*column = -1;
	*nline = 0;
	while (i < parser->nlines)
	{
		if (parser->buffer[i])
		{
			line = parser->buffer[i];
			line += ft_strspn(line, " ");
			size = ft_strcspn(line, " ");
			if (ft_strncmp(line, objp->id, size) == 0)
			{
				*nline = i;
				*column = (line - parser->buffer[i]);
				return (line);
			}
		}
		i++;
	}
	return (NULL);
}

static t_rt_parser_file_context	rt_parser_line_duplicate_err(
	t_rt_parser *parser,
	t_rt_object_parser *objp,
	const char *line,
	const char **tokens
) {
	t_rt_parser_file_context	context;
	size_t						nline;
	int							column;
	const char					*other_line
		= rt_parser_line_find_other(parser, objp, &nline, &column);

	ft_memset(&context, 0, sizeof(t_rt_parser_file_context));
	context.type = FILE_ERR_DUPLICATE;
	context.error_message = "this object is already defined somewhere else";
	context.column = rt_parser_line_token_pos(line, 0);
	context.length = ft_strlen(tokens[0]);
	context.possible_fix = "you can run miniRT with '-n' to allow "
		"duplicate unique objects";
	if (other_line && column != -1)
	{
		context.note.line = nline + 1;
		context.note.column = column;
		context.note.message = "object already defined here";
		context.note.length = ft_strcspn(other_line, " ");
	}
	return (context);
}

RESULT	rt_parser_line_check_unique(t_rt_parser *parser,
			t_rt_object_parser *objp, const char *line,
			const char **tokens)
{
	const t_rt_obj_type	type = (t_rt_obj_type) objp->enum_id;
	t_list				*result;
	t_obj				*obj;
	const char			*name;

	if ((int)type == 0 || (int)type == -1)
		return (OK());
	if (!objp->is_unique || parser->rt->flags.no_unique)
		return (OK());
	name = objp->id;
	if (parser->name_fn)
		name = parser->name_fn(objp->enum_id);
	rt_trace(parser->rt, "checking for duplicate for '%s'\n", name);
	result = parser->result;
	while (result)
	{
		obj = (t_obj *)result->content;
		if (obj->type == type)
			return (ERR_FILE(rt_parser_line_duplicate_err(parser,
						objp, line, tokens)));
		result = result->next;
	}
	return (OK());
}
