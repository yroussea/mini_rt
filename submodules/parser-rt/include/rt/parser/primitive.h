/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:22:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/10 22:47:09 by kiroussa         ###   ########.fr       */
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
 */

/**
 * @brief An enum of the available primitive types.
 */
enum e_rt_primitive
{
	RT_PRIM_COORDINATES = 0,	// t_vec3d
	RT_PRIM_ROTATION,			// t_vec3d (normalized) [-1, 1]
	RT_PRIM_COLOR,				// t_color
	RT_PRIM_INT,				// int
	RT_PRIM_UINT,				// unsigned int
	RT_PRIM_DOUBLE,				// double
	RT_PRIM_ANGLE,				// int [0-180]
	_RT_PRIM_SIZE,				// (last entry, for the enum's size)
};

/**
 * @brief A structure defining a pure primitive parser.
 */
typedef struct s_rt_primitive_parser
{
	enum e_rt_primitive				type;
	struct s_rt_primitive_parser	*next;
}	t_rt_primitive_parser;

# endif // __RT_PARSER_PRIMITIVE_H__
#endif // PRIMITIVE_H
