/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:17:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:57:34 by kiroussa         ###   ########.fr       */
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

typedef const char	*(t_parser_name_fn)(size_t type);

typedef struct s_rt_parser
{
	const t_rt				*rt;
	t_parser_name_fn		*name_fn;
	t_list					*result;
	char					*read_buffer;
	char					**buffer;
	size_t					nlines;
	t_rt_primitive_parser	primitive_parsers[RT_PARSER_MAX_PRIMITIVES];
	t_rt_object_parser		object_parsers[RT_PARSER_MAX_OBJECTS];
}	t_rt_parser;

RESULT	rt_parser_init(t_rt_parser *parser, const t_rt *rt,
			t_parser_name_fn *name_fn, bool add_default);
void	rt_parser_destroy(t_rt_parser *parser);
RESULT	rt_parser_parse(t_rt_parser *parser, const char *filepath);
RESULT	rt_parser_finalize(t_rt_parser *parser);

#  ifdef __RT_PARSER_INTERNAL__

RESULT	rt_parser_buffer_fill(t_rt_parser *parser, const char *filepath);
RESULT	rt_parser_buffer_preproc(t_rt_parser *parser, char *buffer);
RESULT	rt_parser_buffer_sanitize(t_rt_parser *parser);

RESULT	rt_parser_line_check_unique(t_rt_parser *parser,
			t_rt_object_parser *objp, const char *line,
			const char **tokens);
RESULT	rt_parser_line_process(t_rt_parser *parser, size_t index);
size_t	rt_parser_line_token_pos(const char *line, size_t index);
RESULT	rt_parser_line_unknown_type(t_rt_parser *parser, char **tokens,
			const char *line);
RESULT	rt_parser_line_test_process(t_rt_parser *parser, char **tokens,
			const char *line);

#  endif // __RT_PARSER_INTERNAL__

#  define OBJ rt_parser_object_register
#  define OBJ_STEP rt_parser_object_step
#  define OBJ_STEP_OPT rt_parser_object_step_opt
#  define PRIM rt_parser_prim_register

# endif // __RT_PARSER_H_
#endif // PARSER_H
