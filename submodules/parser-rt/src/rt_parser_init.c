/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:39:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 20:07:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/parser.h>
#include <rt/parser/primitive/builtins.h>

static void	rt_parser_init_defaults(t_rt_parser *parser)
{
	rt_parser_prim_register(parser, RT_PRIM_ANGLE, rt_parser_prim_angle);
	rt_parser_prim_register(parser, RT_PRIM_BUMPFILE, rt_parser_prim_bumpmap);
	rt_parser_prim_register(parser, RT_PRIM_CHECKERED,
		rt_parser_prim_checkered);
	rt_parser_prim_register(parser, RT_PRIM_COLOR, rt_parser_prim_color);
	rt_parser_prim_register(parser, RT_PRIM_COORDS, rt_parser_prim_coords);
	rt_parser_prim_register(parser, RT_PRIM_DOUBLE, rt_parser_prim_double);
	rt_parser_prim_register(parser, RT_PRIM_INT, rt_parser_prim_int);
	rt_parser_prim_register(parser, RT_PRIM_NORMAL, rt_parser_prim_normal);
	rt_parser_prim_register(parser, RT_PRIM_UDOUBLE, rt_parser_prim_udouble);
	rt_parser_prim_register(parser, RT_PRIM_UINT, rt_parser_prim_uint);
	rt_parser_prim_register(parser, RT_PRIM_URATIO, rt_parser_prim_uratio);
}

RESULT	rt_parser_init(t_rt_parser *parser, const t_rt *rt,
			t_parser_name_fn *name_fn, bool add_default)
{
	if (!parser || !rt)
		return (ERRS(PARSE_ERR_NULL, "cannot initialize parser with null"
				"arguments"));
	if (!name_fn)
		return (ERRS(PARSE_ERR_NULL, "cannot initialize parser with null"
				"name function"));
	ft_memset(parser, 0, sizeof(t_rt_parser));
	parser->rt = rt;
	parser->name_fn = name_fn;
	if (add_default)
		rt_parser_init_defaults(parser);
	return (OK());
}
