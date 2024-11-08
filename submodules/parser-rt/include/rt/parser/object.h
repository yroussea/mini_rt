/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:11:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/09 00:32:51 by kiroussa         ###   ########.fr       */
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

typedef struct s_rt_object_parser_step
{
	enum e_rt_primitive	type;
	size_t				offset;
}	t_rt_object_parser_step;

typedef struct s_rt_object_parser
{
	const char				*id;
	bool					is_unique;
	size_t					size;
	t_rt_object_parser_step	sequence[RT_PARSER_OBJECT_MAX_STEPS];
	size_t					sequence_size;
	size_t					required;
}	t_rt_object_parser;

RESULT	rt_parser_object_step(t_rt_object_parser *parser, size_t offset,
			enum e_rt_primitive type);

# endif // __RT_PARSER_OBJECT_H__
#endif // OBJECT_H
