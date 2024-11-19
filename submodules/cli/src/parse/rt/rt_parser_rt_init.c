/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_rt_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:25:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 01:18:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/objects.h>
#include <rt/parser.h>
#include <stdbool.h>

RESULT	rt_object_ambient_light(t_rt_object_parser *objp);
RESULT	rt_object_camera(t_rt_object_parser *objp);
RESULT	rt_object_light(t_rt_object_parser *objp);
RESULT	rt_object_sphere(t_rt_object_parser *objp);
RESULT	rt_object_plane(t_rt_object_parser *objp);
RESULT	rt_object_cylinder(t_rt_object_parser *objp);
RESULT	rt_object_cone(t_rt_object_parser *objp);

RESULT	rt_object_define_colors(t_rt_object_parser *objp, RESULT res,
			bool checker, bool bump)
{
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_obj, material.colors), RT_PRIM_COLOR);
	if (checker)
	{
		if (RES_OK(res))
			res = OBJ_STEP_OPT(objp, offsetof(t_obj, material.type),
					RT_PRIM_CHECKERED);
		if (RES_OK(res))
			res = OBJ_STEP_OPT(objp, offsetof(t_obj, material.check_colors),
					RT_PRIM_COLOR);
	}
	if (bump && RES_OK(res))
		res = OBJ_STEP_OPT(objp, offsetof(t_obj, material),
				RT_PRIM_BUMPFILE);
	return (res);
}

RESULT	rt_cli_parser_rt_init(t_rt_parser *parser)
{
	RESULT	res;

	res = OBJ(parser, rt_object_ambient_light);
	if (RES_OK(res))
		res = OBJ(parser, rt_object_camera);
	if (RES_OK(res))
		res = OBJ(parser, rt_object_light);
	if (RES_OK(res))
		res = OBJ(parser, rt_object_sphere);
	if (RES_OK(res))
		res = OBJ(parser, rt_object_plane);
	if (RES_OK(res))
		res = OBJ(parser, rt_object_cylinder);
	if (RES_OK(res))
		res = OBJ(parser, rt_object_cone);
	return (res);
}
