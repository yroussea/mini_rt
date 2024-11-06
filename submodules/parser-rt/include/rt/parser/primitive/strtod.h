/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtod.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:52:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/03 20:55:41 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTOD_H
# define STRTOD_H
# undef STRTOD_H
# ifndef __RT_PARSER_PRIMITIVE_STRTOD_H__
#  define __RT_PARSER_PRIMITIVE_STRTOD_H__

#  include <ft/string.h>
#  include <rt/parser/error.h>

#  define INVALID_CHAR_DIGIT "should be a digit"

#  define INVALID_CHAR_E "exponent notation isn't supported"
#  define FIX_E "replace the exponent notation with a decimal point"

#  define __CTX t_rt_parser_file_context

__CTX	rt_strtod_ctx_char(size_t i, const char *err, const char *fix);

#  undef __CTX

RESULT	rt_strtod_num(const char **strptr, double *result, bool *filled);
RESULT	rt_strtod_frac(const char **strptr, double *result, bool *filled);
RESULT	rt_strtod_midcheck(const char *str, const char *end);
RESULT	rt_strtod_final(const char *str, bool *filled, const char *end);

# endif // __RT_PARSER_PRIMITIVE_STRTOD_H__
#endif // STRTOD_H
