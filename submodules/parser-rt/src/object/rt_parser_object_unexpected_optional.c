/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_unexpected_optional.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:55:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 00:56:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
#include <rt/util.h>

t_rt_parser_file_context	rt_parser_object_unexpected_optional(
	const char *token
) {
	t_rt_parser_file_context	context;

	ft_memset(&context, 0, sizeof(t_rt_parser_file_context));
	context.type = FILE_ERR_TOO_MANY_PARTS;
	context.length = ft_strlen(token);
	context.error_message = "unexpected token";
	context.possible_fix = ft_strdup("this is an optional part you can remove;"
			" is it in the wrong order?");
	return (context);
}
