/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:20:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 20:07:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# undef BUILTINS_H
# ifndef __RT_PARSER_PRIMITIVE_BUILTINS_H__
#  define __RT_PARSER_PRIMITIVE_BUILTINS_H__

#  include <rt/parser.h>
#  include <rt/parser/primitive.h>

RESULT	rt_parser_prim_angle(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_bumpmap(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_checkered(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_color(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_coords(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_double(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_int(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_normal(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_udouble(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_uint(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);
RESULT	rt_parser_prim_uratio(const t_rt_parser *parser,
			const char *slice, void *memory, size_t *size);

# endif // __RT_PARSER_PRIMITIVE_BUILTINS_H__
#endif // BUILTINS_H
