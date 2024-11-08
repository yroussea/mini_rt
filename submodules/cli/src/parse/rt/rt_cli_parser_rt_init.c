/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parser_rt_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:25:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/09 00:48:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/cli/parse/rt.h>
#include <rt/parser.h>

#define REG rt_parser_object_register

RESULT	rt_cli_parser_rt_init(t_rt_parser *parser)
{
	RESULT	res;

	res = OK();
	(void) parser;
	return (res);
}

// t_rt_object_parser	rt_dummy_object(void)
// {
// 	t_rt_object_parser	obj;
//
// 	obj.id = "dummy";
// 	obj.is_unique = true;
// 	obj.size = 16;
// 	obj.sequence_size = 0;
// 	obj.required = 0;
// 	return (obj);
// }
