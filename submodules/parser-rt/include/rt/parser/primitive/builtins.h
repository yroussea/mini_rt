/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:20:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 23:23:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# undef BUILTINS_H
# ifndef __RT_PARSER_PRIMITIVE_BUILTINS_H__
#  define __RT_PARSER_PRIMITIVE_BUILTINS_H__

#  include <rt/parser.h>
#  include <rt/parser/primitive.h>

RESULT	rt_parser_prim_position(t_rt_parser *parser, const char *slice,
			void *memory, size_t *size);

# endif // __RT_PARSER_PRIMITIVE_BUILTINS_H__
#endif // BUILTINS_H
