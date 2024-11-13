/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parser_rt_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:25:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 05:22:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/parser.h>

t_rt_object_parser	rt_dummy_object(void)
{
	t_rt_object_parser	obj;

	ft_memset(&obj, 0, sizeof(t_rt_object_parser));
	obj.id = "BB";
	obj.size = 16;
	obj.sequence_size = 0;
	obj.required = 0;
	return (obj);
}

t_rt_object_parser	rt_dummy_object2(void)
{
	t_rt_object_parser	obj;

	ft_memset(&obj, 0, sizeof(t_rt_object_parser));
	obj.id = "CC";
	obj.is_unique = true;
	obj.size = 16;
	obj.sequence_size = 0;
	obj.required = 0;
	return (obj);
}

RESULT	rt_cli_parser_rt_init(t_rt_parser *parser)
{
	RESULT	res;

	res = rt_parser_object_register(parser, rt_dummy_object());
	if (RES_OK(res))
		res = rt_parser_object_register(parser, rt_dummy_object2());
	return (res);
}
