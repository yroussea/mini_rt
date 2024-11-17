/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_unknown_type.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 05:39:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 22:23:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

static char	*rt_parser_line_known(t_rt_parser *parser)
{
	char	*err_str;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	size = 0;
	while (parser->object_parsers[i].id)
		size += ft_strlen(parser->object_parsers[i++].id) + 2;
	j = i;
	err_str = ft_calloc(size, sizeof(char));
	i = 0;
	while (err_str && parser->object_parsers[i].id)
	{
		ft_strlcat(err_str, parser->object_parsers[i].id, size);
		i++;
		if (i != j)
			ft_strlcat(err_str, ", ", size);
	}
	if (!err_str)
		return (ft_strdup("allocerr"));
	return (err_str);
}

RESULT	rt_parser_line_unknown_type(t_rt_parser *parser, char **tokens,
			const char *line)
{
	t_rt_parser_file_context	context;

	rt_debug(parser->rt, "unknown object identifier: '%s'\n", tokens[0]);
	ft_memset(&context, 0, sizeof(t_rt_parser_file_context));
	context.type = FILE_ERR_UNKNOWN_ID;
	context.error_message = "this object type is unrecognized";
	context.column = rt_parser_line_token_pos(line, 0);
	context.length = ft_strlen(tokens[0]);
	context.possible_fix = ft_strjoins(2, "", 0b01, "known object ids: ",
			rt_parser_line_known(parser));
	if (!context.possible_fix)
		context.possible_fix = ft_strdup("use a valid object identifier");
	return (ERR_FILE(context));
}
