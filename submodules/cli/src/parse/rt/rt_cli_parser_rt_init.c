/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parser_rt_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:25:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 07:43:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/objects.h>
#include <rt/parser.h>

RESULT	rt_object_define_colors(t_rt_object_parser *objp, RESULT res)
{
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_obj, material.colors), RT_PRIM_COLOR);
	if (RES_OK(res))
		res = OBJ_STEP_OPT(objp, offsetof(t_obj, material.type),
				RT_PRIM_CHECKERED);
	if (RES_OK(res))
		res = OBJ_STEP_OPT(objp, offsetof(t_obj, material.check_colors),
				RT_PRIM_COLOR);
	return (res);
}

RESULT	rt_object_plane(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "pl", "plane", sizeof(t_plane));
	res = OBJ_STEP(objp, offsetof(t_plane, point), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_plane, normal), RT_PRIM_NORMAL);
	return (rt_object_define_colors(objp, res));
}

RESULT	rt_object_cylinder(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "cy", "cylinder", sizeof(t_cylinder));
	res = OBJ_STEP(objp, offsetof(t_cylinder, center), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cylinder, axis), RT_PRIM_NORMAL);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cylinder, diameter), RT_PRIM_UDOUBLE);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cylinder, height), RT_PRIM_UDOUBLE);
	return (rt_object_define_colors(objp, res));
}

RESULT	rt_cli_parser_rt_init(t_rt_parser *parser)
{
	RESULT	res;

	res = OBJ(parser, rt_object_plane);
	if (RES_OK(res))
		res = OBJ(parser, rt_object_cylinder);
	return (res);
}
