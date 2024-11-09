/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cylinder.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:15:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/09 17:44:57 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/render/backend/raytracer/objs.h"
#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <math.h>

t_vec3d	rt_backend_raytracer_cylinder_normal(
	const t_ray ray, void *obj)
{
	const t_cylinder	*cy = (t_cylinder *)obj;
	t_vec3d				a;
	t_vec3d				new_point;
	double				m;

	if (cy->surface_type != RONDED)
		return (v3d_mult(&cy->axis,
				-ft_fsign(v3d_dot(&ray.direction, &cy->axis))));
	new_point = v3d_sub(&ray.hit_point, &cy->center);
	m = v3d_dot(&new_point, &cy->axis);
	a = v3d_addmult(&cy->center, &cy->axis, m);
	return (v3d_normsub(&ray.hit_point, &a));
}

static void	rt_backend_raytracer_cylinder_twod_relative_point(
	t_vec3d *relative_coo, const t_ray ray, const t_cylinder *c_cy)
{
	const t_vec3d	hit = v3d_sub(&ray.hit_point, &c_cy->center);
	const double	b = v3d_dot(&hit, &c_cy->axis);
	const t_vec3d	a = v3d_addmult(&c_cy->center, &c_cy->axis, b);
	const t_vec3d	sol = m3d_solv(m3d(c_cy->vec_udir, c_cy->vec_vdir,
				c_cy->axis), v3d_sub(&ray.hit_point, &a));

	relative_coo->x = b;
	relative_coo->y = ft_fsign(sol.y) * \
		acos(sol.x / sqrt(sol.x * sol.x + sol.y * sol.y));
	relative_coo->z = v3d_lensub(&a, &ray.hit_point) - c_cy->diameter / 2;
}

#define RT_RONDED_CYLINDER_LINK_CHECKERBOARD 1
#if RT_RONDED_CYLINDER_LINK_CHECKERBOARD

t_vec3d	rt_backend_raytracer_colors_cylinder(
	const t_ray ray, void *obj)
{
	const t_objs		*cy = (t_objs *)obj;
	const t_cylinder	*c_cy = (t_cylinder *)cy->obj;
	const t_vec3d		colors[2] = {cy->material.colors, (t_vec3d){0, 0, 0}};
	t_vec3d				tmp;

	if (cy->material.type == COLOR)
		return (*colors);
	rt_backend_raytracer_cylinder_twod_relative_point(&tmp, ray, c_cy);
	return (colors[rt_backend_raytracer_checkerboard(
				tmp.x - tmp.z, tmp.y / M_PI * 100)]);
}

#else

t_vec3d	rt_backend_raytracer_colors_cylinder(t_ray ray, void *obj)
{
	const t_objs		*cy = (t_objs *)obj;
	const t_cylinder	*c_cy = (t_cylinder *)cy->obj;
	const t_vec3d		colors[2] = {cy->material.colors, (t_vec3d){0, 0, 0}};
	t_vec3d				tmp;

	if (cy->material.type == COLOR)
		return (*colors);
	if (c_cy->surface_type != RONDED)
	{
		if (c_cy->surface_type == PLANE)
			tmp = v3d_sub(&ray.hit_point, &c_cy->center);
		else
			tmp = v3d_sub(&ray.hit_point, &c_cy->top_center);
		return (rt_backend_raytracer_planar_color(
				tmp, m3d(c_cy->vec_udir, c_cy->vec_vdir, c_cy->axis),
				cy->material.colors, cy->material.type));
	}
	rt_backend_raytracer_cylinder_twod_relative_point(&tmp, ray, c_cy);
	return (colors[rt_backend_raytracer_checkerboard(
				tmp.x, tmp.y / M_PI * 100)]);
}

#endif

#include <stdio.h>
void	rt_backend_raytracer_cylinder(t_objs *obj)
{
	t_cylinder	*cy;
	t_vec3d		tmp;

	cy = obj->obj;
	tmp = v3d(cy->axis.y + cy->axis.z, -cy->axis.x, -cy->axis.x);
	cy->vec_udir = v3d_norm(&tmp);
	tmp = v3d_cross(&cy->axis, &tmp);
	cy->vec_vdir = v3d_norm(&tmp);
	cy->sq_radius = cy->diameter * cy->diameter / 4;
	cy->top_center = v3d_addmult(&cy->center, &cy->axis, cy->height);
	tmp = v3d_addmult(&cy->center, &cy->axis, cy->height / 2);
	//fail malloc..
	rt_backend_raytracer_creat_bonding_box(&cy->bb, tmp,
		m3d(cy->vec_vdir, cy->vec_udir, cy->axis),
		v3d(cy->diameter * sqrt(2) / 4,
		cy->diameter * sqrt(2) / 4, cy->height / 2));
	obj->get_normal = rt_backend_raytracer_cylinder_normal;
	obj->intersection = rt_backend_raytracer_cylinder_intersection;
	obj->get_colors = rt_backend_raytracer_colors_cylinder;
}

t_objs	*cylinder(t_vec3d coo, t_vec3d vector, double height, double diam, t_vec3d colors)
{
	t_objs		*new;
	t_cylinder	*cy;

	cy = rt_malloc_aligned(sizeof(t_cylinder), 32);
	cy->diameter = diam;
	cy->axis = v3d_norm(&vector);
	cy->height = height;
	cy->center = coo;
	new = rt_malloc_aligned(sizeof(t_objs), 32);
	new->type = OBJS;
	new->obj = cy;
	new->material = (t_material){COLOR, colors};
	rt_backend_raytracer_cylinder(new);
	return (new);
}
