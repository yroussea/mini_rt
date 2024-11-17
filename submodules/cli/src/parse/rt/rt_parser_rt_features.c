/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_rt_features.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:14:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 22:14:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/objects.h>
#include <rt/parser.h>
#include <stdbool.h>

RESULT	rt_object_define_colors(t_rt_object_parser *objp, RESULT res,
			bool checker, bool bump);

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
