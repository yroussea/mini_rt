/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtoi.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 06:40:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 10:48:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTOI_H
# define STRTOI_H
# undef STRTOI_H
# ifndef __RT_PARSER_PRIMITIVE_STRTOI_H__
#  define __RT_PARSER_PRIMITIVE_STRTOI_H__

#  include <rt/parser/error.h>
#  include <stddef.h>

RESULT	rt_strtoi(const char **str, int *result, const char *end);

# endif // __RT_PARSER_PRIMITIVE_STRTOI_H__
#endif // STRTOI_H
