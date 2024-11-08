/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:39:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 23:23:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/parser.h>
#include <rt/parser/primitive/builtins.h>

static void	rt_parser_init_defaults(t_rt_parser *parser)
{
	rt_parser_prim_register(parser, RT_PRIM_POSITION, rt_parser_prim_position);
}

RESULT	rt_parser_init(t_rt_parser *parser, const t_rt *rt, bool add_default)
{
	ft_memset(parser, 0, sizeof(t_rt_parser));
	parser->rt = rt;
	if (add_default)
		rt_parser_init_defaults(parser);
	return (OK());
}
