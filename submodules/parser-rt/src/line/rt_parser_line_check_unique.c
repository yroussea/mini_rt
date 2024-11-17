/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_check_unique.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:19:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 22:33:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

// static t_rt_parser_file_context	rt_parser_Line_duplicate_err(
// 	t_rt_parser *parser,
// 	const char *line,
// 	const char **tokens
// ) {
// 	t_rt_parser_file_context	context;
//
// 	ft_memset(&context, 0, sizeof(t_rt_parser_file_context));
// 	context.type = FILE_ERR_DUPLICATE;
// 	context.error_message = "this object type is already defined";
// 	context.column = rt_parser_line_token_pos(line, 0);
// 	context.length = ft_strlen(tokens[0]);
// 	context.possible_fix = ft_strjoins(2, "", 0b01, "object type: ",
// 			parser->name_fn(objp->enum_id));
// 	return (context);
// }

RESULT	rt_parser_line_check_unique(t_rt_parser *parser,
			t_rt_object_parser *objp, const char *line,
			const char **tokens)
{
	// const t_rt_object_type	type = objp->enum_id;
	// t_list					*result;
	// t_obj					*obj;
	//
	// if ((int)type == 0 || (int)type == -1)
	// 	return (OK());
	// result = parser->result;
	// while (result)
	// {
	// 	obj = (t_obj *)result->content;
	// 	if (obj->type == type)
	// 		return (ERR_FILE(rt_parser_Line_duplicate_err(parser, line,
	// 					tokens)));
	// 	result = result->next;
	// }
	// return (OK());
	return (OK());
}
