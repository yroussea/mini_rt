/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_rt_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:14:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 00:21:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/objects.h>
#include <rt/parser.h>
#include <stdbool.h>

RESULT	rt_object_define_colors(t_rt_object_parser *objp, RESULT res,
			bool checker, bool bump);

RESULT	rt_object_sphere(t_rt_object_parser *objp)
{
	RESULT	res;

	rt_parser_object_init(objp, "sp", OBJ_SPHERE, sizeof(t_sphere));
	res = OBJ_STEP(objp, offsetof(t_sphere, center), RT_PRIM_COORDS);
	if (RES_OK(res))
		res = OBJ_STEP(objp, offsetof(t_sphere, radius), RT_PRIM_UDOUBLE);
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
	return (rt_object_define_colors(objp, res, true, true));
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
	return (rt_object_define_colors(objp, res, true, true));
}
