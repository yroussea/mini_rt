/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:17:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/02 09:28:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# undef PARSER_H
# ifndef __RT_PARSER_H__
#  define __RT_PARSER_H__

#  include <ft/data/list.h>
#  include <rt/app.h>
#  include <rt/parser/error.h>
#  include <rt/parser/primitive.h>
// #  include <rt/parser/type.h>

typedef struct s_rt_parser
{
	const t_rt				*rt;
	t_list					*result;
	char					**buffer;
	size_t					nlines;
	// t_list					*type_parsers;
	t_rt_primitive_parser	*primitive_parsers;
}	t_rt_parser;

RESULT	rt_parser_init(t_rt_parser *parser, const t_rt *rt);
void	rt_parser_destroy(t_rt_parser *parser);

void	rt_parser_prim_add(t_rt_parser *parser, t_rt_primitive_parser *parser);

RESULT	rt_parser_parse(t_rt_parser *parser, const char *filepath);

#  ifdef __RT_PARSER_INTERNAL__

RESULT	rt_parser_buffer_fill(const char *filepath, char **buffer,
			size_t *nlines);
RESULT	rt_parser_buffer_preproc(t_rt_parser *parser, char *buffer);
RESULT	rt_parser_buffer_sanitize(t_rt_parser *parser);

#  endif // __RT_PARSER_INTERNAL__

# endif // __RT_PARSER_H_
#endif // PARSER_H
