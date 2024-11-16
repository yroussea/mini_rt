/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parser_rt_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:25:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 20:15:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/objects.h>
#include <rt/parser.h>
#include <stdbool.h>

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
		res = OBJ_STEP_OPT(objp, offsetof(t_obj, material.bumpmap),
				RT_PRIM_BUMPFILE);
	return (res);
}

RESULT	rt_object_ambient_light(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "A", OBJ_AMBIANT_LIGHT, sizeof(t_light));
	res = OBJ_STEP(objp, offsetof(t_light, intensity), RT_PRIM_URATIO);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_obj, material.colors), RT_PRIM_COLOR);
	return (res);
}

RESULT	rt_object_camera(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "C", OBJ_CAMERA, sizeof(t_camera));
	res = OBJ_STEP(objp, offsetof(t_camera, point), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_camera, view_vector), RT_PRIM_NORMAL);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_camera, fov), RT_PRIM_ANGLE);
	return (res);
}

RESULT	rt_object_light(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "L", OBJ_LIGHT, sizeof(t_light));
	res = OBJ_STEP(objp, offsetof(t_light, point), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_light, intensity), RT_PRIM_URATIO);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_obj, material.colors), RT_PRIM_COLOR);
	return (res);
}

RESULT	rt_object_sphere(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "sp", OBJ_SPHERE, sizeof(t_sphere));
	res = OBJ_STEP(objp, offsetof(t_sphere, center), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_sphere, rayon), RT_PRIM_UDOUBLE);
	return (rt_object_define_colors(objp, res, true, true));
}

RESULT	rt_object_plane(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "pl", OBJ_PLANE, sizeof(t_plane));
	res = OBJ_STEP(objp, offsetof(t_plane, point), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_plane, normal), RT_PRIM_NORMAL);
	return (rt_object_define_colors(objp, res, true, true));
}

RESULT	rt_object_cylinder(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "cy", OBJ_CYLINDER, sizeof(t_cylinder));
	res = OBJ_STEP(objp, offsetof(t_cylinder, center), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cylinder, axis), RT_PRIM_NORMAL);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cylinder, diameter), RT_PRIM_UDOUBLE);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cylinder, height), RT_PRIM_UDOUBLE);
	return (rt_object_define_colors(objp, res, true, false));
}

RESULT	rt_object_cone(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "co", OBJ_CONE, sizeof(t_cone));
	res = OBJ_STEP(objp, offsetof(t_cone, center), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cone, axis), RT_PRIM_NORMAL);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cone, theta), RT_PRIM_ANGLE);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_cone, height), RT_PRIM_UDOUBLE);
	return (rt_object_define_colors(objp, res, true, false));
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
