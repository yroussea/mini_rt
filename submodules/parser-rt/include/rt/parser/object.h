/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:11:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:37:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# undef OBJECT_H
# ifndef __RT_PARSER_OBJECT_H__
#  define __RT_PARSER_OBJECT_H__

#  include <rt/parser/error.h>
#  include <stddef.h>

#  define RT_PARSER_OBJECT_MAX_STEPS 16

typedef struct s_rt_object_parser	t_rt_object_parser;

typedef RESULT						t_object_parser_provider_fn(
										t_rt_object_parser *ptr);

typedef struct s_rt_object_parser_step
{
	enum e_rt_primitive	type;
	size_t				offset;
}	t_rt_object_parser_step;

typedef struct s_rt_object_parser
{
	t_rt_parser				*parser;
	const char				*id;
	size_t					enum_id;
	bool					is_required;
	bool					is_unique;
	size_t					size;
	t_rt_object_parser_step	sequence[RT_PARSER_OBJECT_MAX_STEPS];
	size_t					sequence_size;
	size_t					required;
}	t_rt_object_parser;

RESULT	rt_parser_object_register(t_rt_parser *parser,
			t_object_parser_provider_fn *fn);
void	rt_parser_object_init(t_rt_object_parser *objp, const char *id,
			int enum_id, size_t size);

RESULT	rt_parser_object_step(t_rt_object_parser *parser, size_t offset,
			enum e_rt_primitive type);
RESULT	rt_parser_object_step_opt(t_rt_object_parser *parser, size_t offset,
			enum e_rt_primitive type);

RESULT	rt_parser_object_parse(t_rt_object_parser *objp, char **tokens,
			const char *line);
RESULT	rt_parser_object_parse_step(t_rt_object_parser *objp,
			char *token, size_t index, void *memory);

# endif // __RT_PARSER_OBJECT_H__
#endif // OBJECT_H
