/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_incomplete.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:29:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 01:31:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <ft/print.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
#include <rt/util.h>

RESULT	rt_parser_object_incomplete(t_rt_object_parser_step *step,
					char **tokens, const char *line, size_t ntok)
{
	t_rt_parser_file_context	context;

	ft_memset(&context, 0, sizeof(t_rt_parser_file_context));
	context.type = FILE_ERR_MISSING_PART;
	context.column = rt_parser_line_token_pos(line, ntok - 1)
		+ ft_strlen(tokens[ntok - 1]) + 1;
	context.length = 1;
	context.error_message = ft_format("you're missing a '%s'",
			rt_parser_strprim(step->type));
	if (!context.error_message)
		context.error_message = ft_strdup("you're missing an object part");
	return (rt_parse_err_file(context));
}
