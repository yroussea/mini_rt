/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:17:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 06:00:53 by kiroussa         ###   ########.fr       */
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
#  include <rt/parser/object.h>

#  define RT_PARSER_MAX_PRIMITIVES 24
#  define RT_PARSER_MAX_OBJECTS 24

typedef struct s_rt_parser
{
	const t_rt				*rt;
	t_list					*result;
	char					*read_buffer;
	char					**buffer;
	size_t					nlines;
	t_rt_primitive_parser	primitive_parsers[RT_PARSER_MAX_PRIMITIVES];
	t_rt_object_parser		object_parsers[RT_PARSER_MAX_OBJECTS];
}	t_rt_parser;

RESULT	rt_parser_init(t_rt_parser *parser, const t_rt *rt, bool add_default);
void	rt_parser_destroy(t_rt_parser *parser);
RESULT	rt_parser_parse(t_rt_parser *parser, const char *filepath);

#  ifdef __RT_PARSER_INTERNAL__

RESULT	rt_parser_buffer_fill(t_rt_parser *parser, const char *filepath);
RESULT	rt_parser_buffer_preproc(t_rt_parser *parser, char *buffer);
RESULT	rt_parser_buffer_sanitize(t_rt_parser *parser);

RESULT	rt_parser_line_process(t_rt_parser *parser, size_t index);
size_t	rt_parser_line_token_pos(const char *line, char **tokens, size_t index);
RESULT	rt_parser_line_unknown_type(t_rt_parser *parser, char **tokens,
			const char *line);

#  endif // __RT_PARSER_INTERNAL__

RESULT	rt_parser_prim_register(t_rt_parser *parser, enum e_rt_primitive type,
			t_rt_primitive_parser_func *fn);
RESULT	rt_parser_object_register(t_rt_parser *parser,
			t_rt_object_parser objp);

# endif // __RT_PARSER_H_
#endif // PARSER_H
