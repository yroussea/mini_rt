/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:43:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 13:35:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# undef RT_H
# ifndef __RT_PARSE_PARSER_RT_H__
#  define __RT_PARSE_PARSER_RT_H__

#  include <rt/parser.h>

RESULT	rt_cli_parser_rt_init(t_rt_parser *parser);

# endif // __RT_PARSE_PARSER_RT_H__
#endif // RT_H
