/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtod.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:52:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 20:01:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTOD_H
# define STRTOD_H
# undef STRTOD_H
# ifndef __RT_PARSER_PRIMITIVE_STRTOD_H__
#  define __RT_PARSER_PRIMITIVE_STRTOD_H__

#  include <ft/string.h>
#  include <ft/math.h>
#  include <ft/mem.h>
#  include <rt/parser/error.h>

#  define INVALID_CHAR_DIGIT "should be a digit"

#  define INVALID_CHAR_E "exponent notation isn't supported"
#  define FIX_E "replace the exponent notation with a decimal point"

#  define INVALID_MISSING_PARTS "missing both decimal and floating parts"
#  define FIX_MISSING_PARTS "maybe try 0.0"

#  define INVALID_CHAR_SEP "expected a separator"
#  define FIX_SEP "put a comma"

#  define INVALID_CHAR_END "expected end of number"

#  define CTX t_rt_parser_file_context

CTX		rt_strtod_ctx_char(size_t i, const char *err, const char *fix);

RESULT	rt_strtod_num(const char **strptr, double *result, bool *filled);
RESULT	rt_strtod_frac(const char **strptr, double *result, bool *filled);
RESULT	rt_strtod_midcheck(const char *str, const char *end);
RESULT	rt_strtod_final(const char **str, bool *filled, const char *end);

RESULT	rt_strtod(const char **str, double *result, const char *end);

#  undef CTX // t_rt_parser_file_context

# endif // __RT_PARSER_PRIMITIVE_STRTOD_H__
#endif // STRTOD_H
