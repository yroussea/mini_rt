/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:22:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 07:26:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVE_H
# define PRIMITIVE_H
# undef PRIMITIVE_H
# ifndef __RT_PARSER_PRIMITIVE_H__
#  define __RT_PARSER_PRIMITIVE_H__

/**
 * @file primitive.h
 * @brief Defines parsing structures and functions for base/primitive types.
 * @see `struct s_rt_primitive_parser`
 * @see `rt/parser/primitive/builtins.h`
 */

#  include <rt/parser/error.h>
#  include <stddef.h>

// Shadow declaration, see <rt/parser.h>
typedef struct s_rt_parser	t_rt_parser;

/**
 * @brief An enum of the available primitive types.
 */
enum e_rt_primitive
{
	RT_PRIM_COORDS = 0,	// t_vec3d
	RT_PRIM_NORMAL,		// t_vec3d (-1 - 1)
	RT_PRIM_COLOR,		// t_vec3d (rgb, 0.0 - 1.0)
	RT_PRIM_INT,		// int
	RT_PRIM_UINT,		// unsigned int
	RT_PRIM_DOUBLE,		// double
	RT_PRIM_UDOUBLE,	// positive ("unsigned") double
	RT_PRIM_ANGLE,		// int, 0 - 180
	// EXTENSIONS
	RT_PRIM_CHECKERED,	// "checkered" string, indicating optional color next
	RT_PRIM_BUMP,		// "bump" string, indicating bump map string next
	RT_PRIM_FILE,		// a file path, must exist and be readable
	//
	_RT_PRIM_SIZE,		// (last entry, for the enum's size)
};

const char				*rt_parser_strprim(enum e_rt_primitive prim);

/**
 * @brief A function pointer to a primitive parser.
 *
 * @param parser The parser to use.
 * @param slice The string slice to parse.
 * @param memory The memory to write to.
 * @param size The size of the memory to write to.
 *
 * @return A result.
 */
typedef RESULT				t_rt_primitive_parser_func(
								const t_rt_parser *parser,
								const char *slice, void *memory, size_t *size);

/**
 * @brief A structure defining a pure primitive parser.
 */
typedef struct s_rt_primitive_parser
{
	enum e_rt_primitive				type;
	t_rt_primitive_parser_func		*fn;
}	t_rt_primitive_parser;

RESULT					rt_parser_prim_register(t_rt_parser *parser,
							enum e_rt_primitive type,
							t_rt_primitive_parser_func *fn);
t_rt_primitive_parser	*rt_parser_prim_get(
							const t_rt_parser *parser,
							const enum e_rt_primitive type);

# endif // __RT_PARSER_PRIMITIVE_H__
#endif // PRIMITIVE_H
